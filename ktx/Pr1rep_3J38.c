#include <stdio.h>
#include <time.h>
/* dev-c++コンパイラでは，上記の"<"や">"と"stdio.h"との間にスペースを入れると
   コンパイル時に不具合が発生することがあるので，スペースは入れないように */

#define LINEAR 1  /* 1:線形探索，0:二分探索 */
#define NORMAL 0  /* 1:通常版，  0:番兵版   */
#define LOOP   0  /* 1:ループ版，0:再帰版   */

#define N  30000  /* 探索するレコード数 (注意：この値"だけ"を変えても、実際の検索レコード数は増えない） */ 

/* 線形探索 */
int l_search(int data[], int target)
{
    int i, count = 0;
#if NORMAL   /* 通常版 */
    for ( i = 0; i < N; i++ )
        if ( target == data[i] ) {
            return i;
        }
    return -1;
#else        /* 番兵版 */
    /* 実装せよ */
    data[N] = target;
    while(1){
        if(target==data[i])break;
        i++;
    }
    if(i==N)return -1;
    else return i;
    /* dataの一番最後に番兵を追加する */
    /* ループに比較条件は不要（データ中に検索キーがあっても無くても最後に番兵は見つかるから） */
    /* みつかったらループを抜ける */
    /* 番兵しかみつからなかったら-1を返す */
    /* データがみつかったらbreakしたときの添え字の値を返す */
#endif
}

/* クイックソート */
void quick(int data[], int left, int right)
{
    if ((right-left) <= 0)return;
    int left2 = left;
    int right2 = right;
    int pivot = data[left];
    while (1) {
        left++;
        while (data[left] < pivot) left++;
        while (data[right] > pivot) right--;
        if (left >= right) break;
        
        int tmp = data[left];
        data[left] = data[right];
        data[right] = tmp;
    }
    data[left2] = data[right];
    data[right] = pivot;
    //printf("%d,%d¥n",left2,right-1);
    quick(data,left2,right-1);
    //printf("%d,%d¥n",left,right2);
    quick(data,left,right2);
    return;
    /* 前期で作成したquick関数を再利用する(再利用にあたって修正が必要なら、修正後に再利用する) */
    /* クイックソートがまだ完成していない場合は既にできているもので最も速いソートを用いてよい */
}

/* 二分探索 */
int b_search(int data[], int low, int high, int target)
{
    int mid;
#if LOOP 
    /* ループバージョン */
    /* 実装せよ */
    int i = 0;
    while (1) {
        if(high<low)return -1;
        mid = ((high - low)/2)+ low;

        if(data[mid]==target)break;
        else if(data[mid]>=target)high = mid - 1;//下にある
        else if(data[mid]<=target)low  = mid + 1;//上にある
    }
    return mid;
    /* low <= high の間はループ（low > highなら見つからなかった） */
    /* mid に low と high の中間値をセット */
    /* data[mid] より target が小さければ high を mid-1 に */
    /* data[mid] より target が大きければ low を mid+1 に */
    /* data[mid] == target だったらループを抜ける */
    /* 見つかったなら mid を返す */
    /* 見つからなかったなら -1 を返す */
#else
    /* 再帰バージョン */
    /* 実装せよ */
    int t;
    if(low>high)return -1;
    mid = ((high - low)/2)+ low;
    if(data[mid]==target)return mid;
    else if(data[mid]>=target)t = b_search(data,low,mid-1,target);//下にある
    else if(data[mid]<=target)t = b_search(data,mid+1,high,target);//上にある
    return t;
    /* low > high なら見つからなかったということで -1 を返す */
    /* mid に low と high の中間値をセット */
    /* data[mid] より target が小さければ前半部分で再帰 */
    /* data[mid] より target が大きければ後半部分で再帰 */
    /* data[mid] == target だったら見つかったということで mid を返す */
#endif
}

/* メイン */
int main(void)
{
    clock_t start,end;
    int a[N], i, target, work[N+1], index;
    for( i = 0; i < N; i++ ) work[i] = rand() % N;
    start = clock();
#if LINEAR
#else
    quick(work,0,N-1);
#endif
    for( target = N/2-500; target < N/2+500; target++ ) {  // 検索レコード数を変えるには、この辺りを修正する必要がある
#if LINEAR
        index = l_search(work,target);
#else
        index = b_search(work,0,N-1,target);
#endif
        
        /*printf("TARGET=%d: ", target);
        if ( index != -1 )
            printf("○\n");
        else
            printf("×\n");*/
    }
         end = clock();
    printf( "処理時間:%lf[s]\n", (double)(end - start)/ CLOCKS_PER_SEC);
    return 0;
}
