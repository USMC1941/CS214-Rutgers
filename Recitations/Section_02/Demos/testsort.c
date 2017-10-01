// refer to https://stackoverflow.com/questions/13372688/sorting-members-of-structure-array

#include <stdio.h>
#include <stdlib.h>

struct employee{
  char gender[13];
  char name[13];
  int id;
};

int compare(const void *s1, const void *s2){
  struct employee *e1 = (struct employee *)s1;
  struct employee *e2 = (struct employee *)s2;
  //int gendercompare = strcmp(e1->gender, e2->gender);
  //if (gendercompare == 0)  /* same gender so sort by id */
  //  return 0;
  //else
  //  return -gendercompare;
  if (e1->id <= e2->id) {
      return 0;
  }
  else{
    return 1;
  }
}

int main(int argc, char const *argv[]) {
  int i;
  struct employee info[]={{"male","Matt",1234},{"female","Jessica",2345},{"male","Josh",1235}};
  
  for (i = 0; i < 3; ++i) {
    printf("%d\t%s\t%s\n", info[i].id, info[i].gender, info[i].name);
  }

  qsort(info, 3, sizeof(struct employee), compare);

  printf("--------------------after sorting-----------------------\n");
  for (i = 0; i < 3; ++i) {
    printf("%d\t%s\t%s\n", info[i].id, info[i].gender, info[i].name);
  }

  return 0;
}