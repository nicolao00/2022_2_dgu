typedef struct node *node_pointer; 
typedef struct node {
      itemType value; 
      node_pointer next;
};
node_pointer TABLE[10], x, z, temp;
void radixSort(itemType *a, int n) {
      int i,j, cnt, radix, radix_mod =10, cipher=0; 
      i=n; 
      while(i>0) { i=i/10; cipher++; } // cipher : 입력 데이터의 자리수 (ex. 450 -> 3)
      for(i=0; i<cipher; i++) {
            for(j=0; j<n; j++) {
                  cnt=0; radix = (a[j]%radix_mod)/(radix_mod/10); 
                          /* radix_mod = 10 이면 radix는 a[j]의 일의 자리수
                         radix_mod = 100 이면 radix는 a[j]의 십의 자리수 */
                  temp = new node; temp->value = a[j]; temp->next = z; 
                  if(TABLE[radix] == z) {  
                          // z는 list의 끝을 확인하기 위한 노드 포인터 (NULL에 해당)
                        TABLE[radix]=temp; 
                  } else {
                        x=TABLE[radix]; 
                        while(x->next != z) {
                              x=x->next; 
                        }
                        x->next=temp; 
                  }
            }

            for(j=0; j<10; j++) {
                  if(TABLE[j]!=z) {
                        x=TABLE[j]; 
                        while(x!=z) {
                              a[cnt++] = x->value; 
                              temp = x; // 메모리에서 노드를 삭제하기 위해 임시 저장
                              x=x->next; 
                                             delete temp; // 배열에 이미 넣은 노드를 메모리에서 삭제
                        }
                  }
                  TABLE[j]=z; 
            }
            radix_mod*=10; 
      }
}
