#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct Dictionary{

	char eng[15];
	char kor[30];
	struct Dictionary *next;

}Dictionary;

void LinkedList(Dictionary *head){

	head -> next = NULL;
	FILE *fp;

	if((fp = fopen("dic.txt", "r")) == NULL){

		fprintf(stderr, "%s 파일을 열 수 없습니다.\n", "dic.txt");
		exit(1);

	}else{

		while(1){

			Dictionary *node = (Dictionary *)calloc(1, sizeof(Dictionary));
			node -> next = NULL;
			if(fscanf(fp, "%s %s\n", node->eng, node->kor) == EOF)
				break;
			if(head -> next == NULL)
				head->next = node;
			else{

				Dictionary * tmp;
				tmp = head;
				while(tmp->next != NULL){
					tmp = tmp->next;
				}
				tmp -> next = node;
			}
		}
	}
	fclose(fp);
	fp=NULL;
}

void sorting(Dictionary *head){

	Dictionary *dic = head;
	dic = dic->next;
	for(dic; dic->next != NULL; dic=dic->next){

		Dictionary *n = head->next;
		Dictionary *temp = head;
		while(n!=NULL && n->next != NULL){

			if(strcmp(n->eng, n->next->eng) <=0){
				temp = n;
				n=n->next;
				continue;
			}else{

				Dictionary * tmp = n->next;
				n->next = n->next->next;
				tmp->next = n;
				temp->next = tmp;
				temp = tmp;
			}
		}
	}
}


int main(void){


	int num;

	char buf[100];
	while(1){


		system("clear");
		printf(">> 영어 단어 맞추기 프로그램 <<\n");
		printf("1. 영어 단어 맞추기             2. 프로그램 종료\n\n");
		printf("번호를 선택하세요: ");
		scanf("%d", &num);


		Dictionary *head = (Dictionary*)calloc(1, sizeof(Dictionary));
		head->next = NULL;
		LinkedList(head);
		Dictionary *dic = head;
		int count = 0;
		for(dic;dic->next!=NULL;dic=dic->next){

			count++;
		}

		Dictionary *d = head;
		switch(num){


			case 1:

				system("clear");
				printf(">> 영어 단어 맞추기 <<\n");

				int i=0;
				float quiz=0;
				float correct=0;

				for(int i=0;i<count;i++){

					sorting(head);

					printf("%s -> ", d->next->kor);
					scanf("%s", buf);
					d=d->next;

					if(strcmp(".quit", buf)==0){

						break;
					}

					if(strcmp(d->eng, buf) == 0){

						printf("correct!\n");
						correct++;
						quiz++;

					}else{

						printf("incorrect!\n");
						quiz++;
					}

				}

				Dictionary *node = head;
				Dictionary *temp = node;
				while(node != NULL){
					temp = temp->next;
					free(node);
					node = temp;
				}

				if(quiz==0){
					printf("당신의 점수는 0.00 점입니다.");
				}else{

					printf("당신의 점수는 %.2f 점입니다.", (correct/quiz)*100);
				}
				getchar();
				break;

			case 2:

				system("clear");
				exit(0);
		}
		getchar();

	}
}






