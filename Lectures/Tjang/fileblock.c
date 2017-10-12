// Courtesy Angrave et al, UIUC
// Disk size:
#define MAX_INODE (1024)
#define MAX_BLOCK (1024 * 1024)

// Each block is 4096 bytes:
typedef char[4096] block_t;

// A disk is an array of inodes and an array of disk blocks:
struct inode[MAX_INODE] inodes;
block[MAX_BLOCK] blocks;


struct inode {
 int[10] directblocks; // indices for the block array i.e. where to the find the file's content
 long size;
 // ... standard inode meta-data e.g.
 int mode, userid, groupid;
 time_t ctime, atime, mtime;
}

char readbyte(inode* inode, long position) {
  if(position < 0 || position >= inode->size) {
    return -1; // invalid offset
  }

  int block_count = position / 4096;
  int offset = position % 4096;

  // block count better be 0..9 !
  int physical_idx = lookup_physical_block_index(inode, block_count );

  // sanity check that the disk block index is reasonable...
  assert(physical_idx >= 0 && physical_idx < MAX_BLOCK);

  // read the disk block from our virtual disk 'blocks' and return the specific byte
  return blocks[physical_idx][offset];
}

int lookup_physical_block_index(inode*inode, int block_count) {
  assert(block_count >= 0 && block_count < 10);
  return inode->directblocks[ block_count ];  // returns an index value between [0, MAX_BLOCK)
}


struct inode {
 int[10] directblocks; // if size < 4KB, then only the first one is valid
 int indirectblock; // valid value when size >= 40KB
 int size;
 //...
}

int lookup_physical_block_index(inode* inode, int block_count) {
  assert(sizeof(int) == 4); // Warning this code assumes an index is 4 bytes!
  assert(block_count >= 0 && block_count < 1024 + 10);  // 0 <= block_count < 1034

  if(block_count < 10) {
     return inode->directblocks[ block_count ];
  }

  // read the indirect block from disk:
  block_t* oneblock = & blocks[ inode->indirectblock ];

  // Treat the 4KB as an array of 1024 pointers to other disk blocks
  int* table = (int*) oneblock;

  // Look up the correct entry in the table
  // Offset by 10 because the first 10 blocks of data are already accounted for
  return table[ block_count - 10 ];
}
