#include <stdio.h>
void bable(int[]);
void wash(int[]);
void sounyu(int[]);
void change(int[]);


int kaisu = 0;
int num = 0;

void main()
{
	int i=0,j,small;
	int check;
	char name[255];
	int moto[1024] = {0};
	int *aho;
	char s1[10],s2[10];
	
	printf("�t�@�C��������͂��Ă��������D\n");
	scanf("%s",&name);
	FILE *fp;
	FILE *fp2;
	sprintf(s1,"%s.txt",name);
	fp = fopen(s1,"r"); //�t�@�C���W�J
	if(fp==NULL){
		printf("���s\n");
		return;
	}
	sprintf(s2,"%s.c",name);
	fp2 = fopen(s2,"w");
	if(fp2==NULL){
		printf("���s\n");
		return;
	}
	while(fscanf(fp,"%d",&moto[i])==1){ //�ǂݍ���
		i++;
	}
	num = sizeof moto /sizeof moto[0];
	aho = (int *)malloc(num*sizeof(int));
	if (aho==NULL) {
		printf("** out of memory **\n");
		exit(1);
	}
	for(i=0;i<num;i++){
		aho[i] = moto[i];
	}
	//�\�[�g�A���S���Y���̑I��
	do{
		printf("�g�p����\�[�g�A���S���Y����I�����ԍ�����͂��Ă�������\n");
		printf("1:�o�u���\�[�g\n");
		printf("2:�I���\�[�g\n");
		printf("3:�}���\�[�g\n");
		scanf("%d",&check);
		if(check==1){
			bable(aho);
		}else if(check==2){
			wash(aho);
		}else if(check==3){
			sounyu(aho);
		}else {
			printf("�G���[�D������x�J��Ԃ��Ă��������D\n");
			check = 0;
		}
	}while(check==0);
	do{
		printf("�����Ȃ�1,�~���Ȃ�0����͂��Ă��������D");
		scanf("%d",&check);
		if(check==1);
		else if(check==0)change(aho);
		else {
			printf("�G���[�D������x�J��Ԃ��Ă��������D\n");
			check = 3;
		}
	}while(check==3);
	printf("\n�\�����܂�...\n");
	for(i=0;i<num;i++){
		printf("%d ",aho[i]);
		fprintf(fp2,"%d\n",aho[i]);
	}
	printf("�񐔁F%d\n",kaisu);
	return;
}

void bable(int moto[]){
	int i,a,j;
	for(i=num-1;i>0;i--){
		for(j=0;j<i;j++){
			if(moto[j]>moto[j+1]){
				a = moto[j+1];
				moto[j+1] = moto[j];
				moto[j] = a;
			}
		}
	}
}

void wash(int moto[]){
	int i,a,j,count=0,small=0;
	for(j=0;j<num;j++){
		small = j;
		for(i=j+1;i<num;i++){
			if(moto[small]>moto[i]){
				small = i;
			}
		}
		a = moto[j];
		moto[j] = moto[small];
		moto[small] = a;
		kaisu++;
	}
}

void sounyu(int moto[]){
	int i,a,j,count=0,small;
	for(i=1;i<num;i++){
		small = moto[i];
		for(j=i;j>=1 && moto[j-1]>small;j--){
			moto[j] = moto[j-1];
			kaisu++;
		}
		moto[j] = small;
	}
}

void change(int moto[]){
	int i,j=num-1,ch;
	for(i=0;i<100;i++,j--){
		ch = moto[i];
		moto[i] = moto[j];
		moto[j] = ch;
		kaisu++;
	}
}