//英単語テスト
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct tango {
	char english[20];
	char japan[30];
	int no;		//正解となる数字を格納
};


bool hantei(int ans, int a);
FILE* fp1(void);
FILE* fp2(void);
FILE* fp3(void);
FILE* fp4(void);


int main() {
	int true_n = 0;			//正解数を保持
	int false_n = 0;		//不正解数を保持
	int false_list[20] = { 0 };	//不正解のリストを配列で保持
	int tango_c;
	int ans;
	char str[25];
	FILE* (* pm[4])(void);	//関数ポインタの配列の宣言

	//関数ポインタをそれぞれの関数を指すようにする
	pm[0] = fp1;
	pm[1] = fp2;
	pm[2] = fp3;
	pm[3] = fp4;


	srand((unsigned int)time(NULL));	//時刻を種に乱数の元を生成


	tango all_a[100];	//ファイル内の全ての単語を格納
	tango a[100];		//ファイル内の全ての単語 all_a から一部の単語を格納
		

	printf("1～4の中で使用する単語セットは？（1～4を入力）");
	int num;
	scanf_s("%d", &num);
	FILE* fp = (pm[num - 1])();		//関数ポインタで呼び出す関数を指定、戻り値のファイルポインタを、FILE*型のfpに渡す


	int all_a_c = 0;
	while (fscanf(fp, "%s%s", all_a[all_a_c].english, all_a[all_a_c].japan) != EOF) {
		all_a_c++;		//全ての単語数をカウント。EOFまで全ての単語をファイルから入力
	}
	fclose(fp);


	printf("単語一覧を表示しますか？（yes…1  no…0）");
	scanf_s("%d", &num);
	if (num == 1) {
		for (int i = 0; i < all_a_c; i++) {
			printf("%-30s%s", all_a[i].english, all_a[i].japan);
			printf("\n");
		}
	}
	else
		printf("表示しません\n");


	printf("何かキーを押してください\n");
	scanf("%s", str);	//何かキーが入力されたらコンソールクリア
	system("cls");		//コンソールクリア

	printf("%d個の英単語があります。\n何問テストしますか？：", all_a_c);
	scanf("%d", &tango_c);



	//全ての単語が格納されているall_aをランダムでテスト数tango_c個分a[]にコピー。以後、a[]をもとにテストしていく
	for (int i = 0; i < tango_c; i++) {
		a[i] = all_a[rand() % (all_a_c + 1)];		//all_a配列の添え字は乱数(0～全ての単語数all_a_c)
	}

	for (int i = 0; i < tango_c; i++) {
		a[i].no = 1 + rand() % 4;		//noメンバには正解となる数字1～4のいずれかを格納する
	}


	
	//ダミーを入力
	char dummy[100][30];
	fp = fopen("dummy.txt", "r");
	int dummy_c = 0;
	while (fscanf(fp, "%s", dummy[dummy_c]) != EOF) {
		dummy_c++;
	}
	fclose(fp);



	printf("適当なキーを入力してください");
	scanf("%s", str);	//何かキーが入力されたらコンソールクリア
	system("cls");		//コンソールクリア

	printf("単語テストを始めます\n正解だと思う数字を半角で入力してください\n\n");

	int raound = 1;
	int i = 0;
	while (true_n != tango_c) {
		true_n = 0;
		false_n = 0;
		for (int k = 0; k < tango_c; k++) {

			printf("%d門.  %s\n", k + 1, a[k].english);

			//選択肢の表示
			for (int j = 1; j < 5; j++) {
				if (j == a[k].no) {
					printf("  (%d) %s\t", j, a[k].japan);
				}
				else
					printf("  (%d) %s\t", j, dummy[rand() % dummy_c]);

			}
			printf("\n\n");

			printf("答えを半角数字で入力して下さい：");
			scanf_s("%d", &ans);
			if (hantei(ans, a[k].no)) {
				printf("正解！\n\n\n\n");
				true_n++;		//正解数
			}
			else {
				printf("ブッブー\n");
				printf("%-20s%s\n\n\n", a[k].english, a[k].japan);
				false_n++;		//不正解数
				false_list[i++] = k;		//不正解リスト
			}
		}
		printf("正解数：%d\t不正解数：%d\n", true_n, false_n);



		if (true_n == tango_c)
			printf("全問正解です\n");
		else {
			printf("\n\n間違えた問題と解答を表示します\n");
			for (int h = 0; h < false_n; h++) {
				printf("%-20s\t%s\n", a[false_list[h]].english, a[false_list[h]].japan);	//配列の添え字が入れ子になっていることに注意
			}
			

			printf("適当なキーを入力してください");
			scanf("%s", str);	//何かキーが入力されたらコンソールクリア
			system("cls");		//コンソールクリア


			printf("\n全問正解するまで終わりません\n\n\n\n\n\n");
			printf("第%dラウンド\n\n", ++raound);
		}

	}
	
}


//真または偽を返すbool型の関数
bool hantei(int ans, int a) {
	return (ans == a);	//条件が成立すれば真を、成立しなければ偽を返す
}


FILE* fp1(void) {
	FILE* fp = fopen("tango.txt", "r");
	if (fp == NULL)
		printf("ファイルが開けません\n");

	return fp;
}


FILE* fp2(void) {
	FILE* fp = fopen("toeic800.txt", "r");
	if (fp == NULL)
		printf("ファイルが開けません\n");

	return fp;
}


FILE* fp3(void) {
	FILE* fp = fopen("tango2.txt", "r");
	if (fp == NULL)
		printf("ファイルが開けません\n");

	return fp;
}


FILE* fp4(void) {
	FILE* fp = fopen("tango3.txt", "r");
	if (fp == NULL)
		printf("ファイルが開けません\n");

	return fp;
}



/*
英単語テスト
英単語を表示し、１～４の該当する日本語を選択してテストを行う
英語と二本語訳がついとなるよう構造体配列を利用する
英単語と日本語訳のセットはいくつかのファイルの中から一つ選び、読み込む
1～4の選択肢のうち一つは正解とし、それ以外の3つはダミーデータとして不正解にする
ダミーデータはdummy.txtから読み込む
ファイルを編集することでオリジナルの英単語テストを作れる
*/


/*
英語とその日本語訳が対となったファイルを複数用意する。
それぞれのファイルを読み込み、読み込んだファイルをファイルポインタとして返す関数をファイル数分用意する。
FILE* fp1(void);
FILE* fp2(void);など

それぞれの関数のアドレスを格納する関数ポインタを配列で用意する。
FILE* (*pm[])(void); 
関数ポインタ pm[n] = 関数 fp
で、関数ポインタの配列で関数を呼び出せるようにする。これにより要素数を指定するだけで場合に応じた関数を簡単に呼び出せる。
*/
