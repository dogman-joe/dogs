#include "stdint.h"
#include "string.h"
#include "drivers.h"

#define FDT_BEGIN_NODE 0x01
#define FDT_END_NODE 0x02
#define FDT_PROP 0x03
#define FDT_NOP 0x04
#define FDT_END 0x09

typedef struct {
  uint32_t magic; /* 0xD00DFEED */
  uint32_t size; /* includes header and data */
  uint32_t struct_offset; /* offset of struct block */
  uint32_t strings_offset; /* offset of strings block */
  uint32_t memory_offset; /* offset of memory block */
  uint32_t version; /* version of dtb (17) */
  uint32_t min_version; /* minimum version (16) */
  uint32_t cpu_id; /* id of boot cpu */
  uint32_t strings_size; /* size of strings block */
  uint32_t struct_size; /* size of struct block */
} dtb_header;

struct fdt_reserved_mem_entry {
  uint64_t base;
  uint64_t length;
};

typedef struct {
  uint32_t length;
  uint32_t name_offset;
} fdt_property;

/* TODO: think about replacing these with dynamic memory alloc */
uint8_t *buf;
char prop_value[0x100];
char prop_sub_value[0x100];
dt_node_info return_node;

/* TODO: add DT lib init function to detect these in root node */
size_t parent_size_cells = 0;
size_t parent_address_cells = 0;

dtb_header *dtb_head;

int check_fdt_header(dtb_header *head) {
  return 0;
}

uint32_t be_32(uint32_t n) {
  uint32_t temp = 0;

  temp |= ((n >> 0) & 0xFF) << 24;
  temp |= ((n >> 8) & 0xFF) << 16;
  temp |= ((n >> 16) & 0xFF) << 8;
  temp |= ((n >> 24) & 0xFF);

  return temp;
}

uint32_t* align32(uint32_t *n) {
  uint32_t rem = (uint64_t)n % 4 == 0 ? 4 : (uint64_t)n % 4;

  return (uint32_t *)((uint64_t)n + (4 - rem));
}

uint32_t check_compatible(char *compatible_val, const char *name) {
  if (strcmp((char *)((uint64_t)compatible_val), name) == 0) {
    return 1;
  }

  return 0;
}

uint32_t* find_compatible_traverse(uint32_t **node,
      uint32_t *string_ptr, const char *name, uint32_t address_cells,
      uint32_t size_cells) {
  uint32_t node_name_len;
  uint32_t *struct_ptr = *node, *ret;
  fdt_property *cur_property;

  /* check to ensure begining of structs is BEGIN_NODE */
  if (be_32(*(uint32_t *)((uint64_t)buf + (uint64_t)struct_ptr))
        != FDT_BEGIN_NODE) {
    return 0;
  }

  struct_ptr++;

  node_name_len = strlen((char *)((uint64_t)buf + (uint64_t)struct_ptr)) + 1;

  struct_ptr = (uint32_t *)align32((uint32_t *)
        ((uint64_t)struct_ptr + (uint64_t)node_name_len));

  while (be_32(*(uint32_t *)
        ((uint64_t)buf + (uint64_t)struct_ptr)) != FDT_END_NODE) {
    if (be_32(*(uint32_t *)
          ((uint64_t)buf + (uint64_t)struct_ptr)) == FDT_BEGIN_NODE) {
      ret = find_compatible_traverse(&struct_ptr,
            string_ptr, name, address_cells, size_cells);
      if (ret) {
        return ret;
      }
    } else if (be_32(*(uint32_t *)
          ((uint64_t)buf + (uint64_t)struct_ptr)) == FDT_PROP) {
      struct_ptr++;
      cur_property = (fdt_property *)((uint64_t)buf + (uint64_t)struct_ptr);

      struct_ptr = (uint32_t *)
            ((uint64_t)struct_ptr + (uint64_t)sizeof(fdt_property));

      if (strcmp((char *)((uint64_t)buf + (uint64_t)string_ptr +
            (uint64_t)be_32(cur_property->name_offset)),
            "#address-cells") == 0) {
        memcpy(prop_value, (uint8_t *)((uint64_t)buf +
              (uint64_t)struct_ptr), be_32(cur_property->length));
        address_cells = be_32(*(uint32_t *)prop_value);
      }
      if (strcmp((char *)((uint64_t)buf + (uint64_t)string_ptr +
            (uint64_t)be_32(cur_property->name_offset)),
            "#size-cells") == 0) {
        memcpy(prop_value, (uint8_t *)((uint64_t)buf +
              (uint64_t)struct_ptr), be_32(cur_property->length));
        size_cells = be_32(*(uint32_t *)prop_value);
      }

      if (strcmp((char *)((uint64_t)buf + (uint64_t)string_ptr +
            (uint64_t)be_32(cur_property->name_offset)), "compatible") == 0) {
        memcpy(prop_value, (char *)((uint64_t)buf + (uint64_t)struct_ptr),
              be_32(cur_property->length));

        if (check_compatible(prop_value, name)) {
          parent_address_cells = address_cells;
          parent_size_cells = address_cells;
          return *node;
        }
      }
      struct_ptr = align32((uint32_t *)
            ((uint64_t)struct_ptr + (be_32(cur_property->length))));
      }
    }

  struct_ptr++;

  *node = struct_ptr;

  return 0;
}

int parse_node_info(uint32_t *node, uint32_t *string_ptr) {
  uint32_t *struct_ptr = node;
  fdt_property *cur_property;
  uint32_t node_name_len;
  uint32_t reg_val[32];

  /* check to ensure begining of structs is BEGIN_NODE */
  if (be_32(*(uint32_t *)
        ((uint64_t)buf + (uint64_t)struct_ptr)) != FDT_BEGIN_NODE) {
    return 1;
  }

  struct_ptr++;

  node_name_len = strlen((char *)((uint64_t)buf + (uint64_t)struct_ptr)) + 1;

  struct_ptr = (uint32_t *)
        align32((uint32_t *)((uint64_t)struct_ptr + (uint64_t)node_name_len));

  while (be_32(*(uint32_t *)
         ((uint64_t)buf + (uint64_t)struct_ptr)) != FDT_END_NODE) {
    /* should be leaf node */
    if (be_32(*(uint32_t *)
          ((uint64_t)buf + (uint64_t)struct_ptr)) == FDT_BEGIN_NODE) {
      return 1;
    } else if (be_32(*(uint32_t *)
          ((uint64_t)buf + (uint64_t)struct_ptr)) == FDT_PROP) {
      struct_ptr++;
      cur_property = (fdt_property *)((uint64_t)buf + (uint64_t)struct_ptr);

      struct_ptr = (uint32_t *)
            ((uint64_t)struct_ptr + (uint64_t)sizeof(fdt_property));

      if (strcmp((char *)((uint64_t)buf + (uint64_t)string_ptr +
            (uint64_t)be_32(cur_property->name_offset)), "reg") == 0) {
        memcpy(&reg_val, (uint32_t *)((uint64_t)buf + (uint64_t)struct_ptr),
              be_32(cur_property->length));

        for (int i = 0, j = 0; i < cur_property->length / 4; ) {
          if (parent_address_cells == 2) {
            return_node.reg_vals[j++] =
                  be_32(reg_val[i]) + be_32(reg_val[i + 1]);
          } else {
            return_node.reg_vals[j++] = be_32(reg_val[i]);
          }
          i += parent_address_cells;

          if (parent_size_cells == 2) {
            return_node.reg_vals[j++] =
                  be_32(reg_val[i]) + be_32(reg_val[i + 1]);
          } else {
            return_node.reg_vals[j++] = be_32(reg_val[i]);
          }
          i += parent_size_cells;
        }
      }
        struct_ptr = align32((uint32_t *)
              ((uint64_t)struct_ptr + (be_32(cur_property->length))));
    }
  }

  return 0;
}

dt_node_info* find_compatible(dtb_header *head, const char *name) {
  uint32_t *struct_ptr = (uint32_t *)(uint64_t)be_32(head->struct_offset);
  uint32_t *string_ptr = (uint32_t *)((uint64_t)be_32(head->strings_offset));
  uint32_t *ret = 0;

  buf = (uint8_t *)head;

  ret = find_compatible_traverse(&struct_ptr, string_ptr, name, 0, 0);

  if (ret) {
    parse_node_info(ret, string_ptr);

    return &return_node;
  }

  return 0;
}
