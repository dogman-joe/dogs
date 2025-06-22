#ifndef DOGTB_H_
#define DOGTB_H_

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

dt_node_info* find_compatible(const dtb_header *head, const char *name);


#endif   /* DOGTB_H_ */
