#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)	//エラー回避
#define WEEKS 6																			//週数
#define MAX_HOLI_TBL 4																	//祝日データ用
#define SPRING_EQ 0																		//春分計算用
#define FALL_EQ 1																		//秋分計算用
#define BIRTH_MARK 0x80																	//誕生日マーク
#define TRANS_MARK 0x40																	//振替祝日マーク
#define HOLI_MARK 0x20								
#define COLOR_RED		"\033[31m"	// 赤色
#define COLOR_CYAN		"\033[36m"	// 水色
#define COLOR_WHITE		"\033[37m"// 白色


enum M_LIST { 
	JAN, FEB, MAR, APR, MAY, JUN, JUL, 
	AUG, SEP, OCT, NOV, DEC, N_MONTH };
enum W_LIST { 
	SUN, MON, TUE, WED, THU, FRI, SAT, N_WEEK };

char mdays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };//月の日数
// 祝日のデータテーブル
char holidays[N_MONTH][MAX_HOLI_TBL] = {
		{1,-2, 0,0},		//  1月、元旦、成人の日
		{11,23,0,0},		//  2月、建国記念日、令和天皇誕生日
		{21,0,0,0},		//  3月、春分の日(計算で算出)
		{29,0,0,0},		//  4月、昭和の日
		{3,4,5,0},		//  5月、憲法記念日、みどりの日、子供の日
		{ 0,0,0,0},		//  6月、なし
		{-3,0,0,0},		//  7月、海の日
		{11,0,0,0},		//  8月、山の日
		{-3,23,0,0},	//  9月、敬老の日、秋分の日(計算で算出)
		{-2,0,0,0},		// 10月、体育の日
		{3,23,0,0},		// 11月、文化の日、勤労感謝の日
		{ 0,0,0,0}		// 12月、なし(23日の平成天皇誕生日はなし)
};

int oneday(int year);
int checku(int year);
char calendar(char cal_tbl[N_MONTH][WEEKS][N_WEEK], int year);
char youbi(int year, int month, int day);
void prt_calen(char calen_tbl[N_MONTH][WEEKS][N_WEEK],int year,int col_MAX);
char holiday(int year);
int h_calender(char calen_tbl[N_MONTH][WEEKS][N_WEEK],int oneday,int bmon,int bday);

int main(void) {
	int bday = 0;
	int bmon = 0;
	int year;
	int col;
	int col_MAX=0;
	//int month;
	//int day;
	int u; //入力された値がうるう年だったかどうか
	//int bw;//入力された誕生日の曜日
	int monthdaysum = 0; // 入力された誕生日の月までの合計の日数
	char calen_tbl[N_MONTH][WEEKS][N_WEEK];
		printf("西暦を入力してください：");
		if(scanf("%d", &year)!=1)return 1;
		printf("列：");
		(void)scanf("%d", &col_MAX);


	//うるう年の判定
	u = checku(year);// うるう年であれば2月を29日に変更
	if (u == 0)
	{
		printf("閏年\n");
		mdays[FEB] = 29;
	}
	else {
		mdays[FEB] = 28;
	}
	//calendar(calen_tbl, year);
	h_calender(calen_tbl,oneday(year), bmon, bday);
	prt_calen(calen_tbl, year,col_MAX);
	return 0;
}
//入力された西暦の1月1日の曜日を返す
int oneday(int year) {
	int sumday;// 入力された西暦までの累計日数
	int dayw;// 曜日計算
	sumday = (((year - 1) * 365) + ((year - 1) / 4) - ((year - 1) / 100) + (year - 1)/400)+1;//入力された1月1日までの日数
	dayw = sumday % 7;

	return dayw;
}
//うるう年の判定
int checku(int year) {
	int result ; // 平年にする
	result = (year % 400 == 0 || (year %4 == 0 && year % 100 != 0))?0:-1;
	return result;
}
//カレンダー
char calendar(char cal_tbl[N_MONTH][WEEKS][N_WEEK],int year) {
	char month;
	char count;
	char day;
	char weeks;
	char week;

	//1年分のカレンダーを作成
	for ( int i = 0; i < N_MONTH ;i++)
	{
		for (int j = 0; j < WEEKS; j++)
		{
			for (int k = 0; k < N_WEEK; k++)
			{
				cal_tbl[i][j][k] = 0;
			}
		}
	}
	for (month = JAN; month < N_MONTH; month++)
	{
		count = 1;
		day = youbi(year, month, 1);

		for (weeks = 0; weeks < 6; weeks++) {
			for (week = SUN; week < N_WEEK; week++)
			{
				if (weeks == 0&&count==1)week = day;//１週目の時の例外処理

					cal_tbl[month][weeks][week] = count;
					count++;
					if (count > mdays[month])break;
			}
			if (count > mdays[month])break;
		}
	}
	return 0;
}
//year年month月day日が何曜日か
char youbi(int year,int month,int day) {
	int sum = oneday(year);
	int nw;//newweek
	for (int i = 0; i < month; i++) {
		sum += mdays[i];
	}
	nw = (sum + day - 1) % 7;
	return nw;
}
//出力
void prt_calen(char calen_tbl[N_MONTH][WEEKS][N_WEEK], int year,int col_MAX)
{
	int week;
	int col;
	int m = 0;
	for (int month = JAN; month < N_MONTH; month+=col_MAX) {
		for (int weeks = -2; weeks < WEEKS; weeks++) {
			for (int col = 0; col < col_MAX; col++){
				if (weeks == -2) {
					//月の出力
					
					printf("%d年%d月              ",year, m + 1);
					m++;
				}
				else {
					if (weeks == -1) {
						printf("\033[31m");
						printf(" 日");
						printf("\033[39m");
						printf(" 月 火 水 木 金");
						printf("\033[36m");
						printf(" 土");
						printf("\033[36m");

					}
					else {
						//日付の出力
						for (week = SUN; week < N_WEEK; week++) {
							if (calen_tbl[month+col][weeks][week] == 0) {
							
								printf("   ");
							}
							else {
								if (calen_tbl[month+col][weeks][week] & HOLI_MARK) {
									printf("\033[31m");
									printf("*");
									printf("\033[31m");
								}
								else if (calen_tbl[month+col][weeks][week] & TRANS_MARK) {
									printf("\033[31m");
									printf("+");
									printf("\033[31m");
								}
								else {
									printf(" ");
								}
								printf("\033[37m%2d", calen_tbl[month+col][weeks][week] & 0x1F);

							}

						}

					}

				}
			
			}
			printf("\n");
		}

	}
}
//春分、秋分の日の計算式
char holiday(int year) {
	int springEQ;	// 求める春分の日
	int fallEQ;		// 求める秋分の日
	if (year <= 1899) {
		springEQ = (int)(19.8277 + 0.242194 * (year - 1980.0) - ((year - 1983) / 4));
		fallEQ = (int)(22.2588 + 0.242194 * (year - 1980.0) - ((year - 1983) / 4));
	}
	else if (year >= 1900 && year <= 1979) {
		springEQ = (int)(20.8357 + 0.242194 * (year - 1980.0) - ((year - 1983) / 4));
		fallEQ = (int)(23.2588 + 0.242194 * (year - 1980.0) - ((year - 1983) / 4));
	}
	else if (year >= 1980 && year <= 2099) {
		springEQ = (int)(20.8431 + 0.242194 * (year - 1980.0) - ((year - 1980) / 4));
		fallEQ = (int)(23.2488 + 0.242194 * (year - 1980.0) - ((year - 1980) / 4));
	}
	else if (year >= 2100) {
		springEQ = (int)(21.851 + 0.242194 * (year - 1980.0) - ((year - 1980) / 4));
		fallEQ = (int)(24.2488 + 0.242194 * (year - 1980.0) - ((year - 1980) / 4));
	}
	holidays[MAR][SPRING_EQ] = springEQ;	// 春分の日を入れる
	holidays[SEP][FALL_EQ] = fallEQ;		// 秋分の日を入れる

	return 0;
}



//祝日マークを入れる
/*
void h_calender(char calen_tbl[N_MONTH][WEEKS][N_WEEK], int year) {
	char day;// 日にちを1に、行を0にする　　今までの処理
	char weeks;
	char week;
	char month;
	char holi;
	
	holi = holidays[3][0];
	for (month = JAN; month <= DEC; month++) {
		//<月初め>
		day = 1;// 日にちを1に、行を0にする　　今までの処理
		weeks = 0;
		//祝日カウント = 0; // 祝日のカウントをクリア


		for (int h = 0; h < MAX_HOLI_TBL; h++)
		{
			holi = holidays[month][h];
			if (holi == 0) {
				break;
			}
			if (holi > 0) {

				for (weeks = 0; weeks < WEEKS; weeks++) {
					for (week = SUN; week < N_WEEK; week++) {
					

						if (calen_tbl[month][weeks][week] == holi) {
							calen_tbl[month][weeks][week] |= HOLI_MARK;
							holi++;
						}
					}
				}
			}
			else {
				int mon_count = 0;
				for ( weeks = 0; weeks < WEEKS; weeks++) {
					if ((calen_tbl[month][weeks][MON] & HOLI_MARK) != 0) {
						mon_count--;

						if (calen_tbl[month][weeks][MON] == holi) {
							calen_tbl[month][weeks][MON] |= HOLI_MARK;
							holi++;

						}
					}
				}
			}
		
		}
	}
}
*/
//祝日マークを入れる
int h_calender(char calen_tbl[N_MONTH][WEEKS][N_WEEK],int oneday,int bmon,int bday) {
	char month;
	char day;
	int weeks;
	char holi_cnt;
	char mon_cnt;
	char week = oneday;
//while (calen_tbl[JAN][0][week] != 1)week++;
	for(int i=0;i<N_MONTH;i++)
	{
		for (int j = 0; j < WEEKS; j++)
		{
			for (int k = 0; k < N_WEEK; k++)
			{
				calen_tbl[i][j][k] = 0;
			}
		}
	}
	for (month = JAN; month <= DEC; month++) {
		//<月初め>
		day = 1;
		weeks = 0; //日にちを1に、行を0にする　
		holi_cnt = 0;// 祝日のカウントをクリア
		mon_cnt = 0; // 月曜日のカウントをクリア  
		while (day <= mdays[month])
		{
			if (week == MON) { // 今日が決曜日であれば、 

				mon_cnt++;//月曜日のカウントを + 1する
			}
			calen_tbl[month][weeks][week] |= day;
			
			if (holidays[month][holi_cnt] == day) // 固定日の祝日が一致なら
			{
				calen_tbl[month][weeks][week] |= HOLI_MARK; // 祝日マークを入れる
				/*if (calen_tbl[month][weeks][week] & TRANS_MARK) {
					calen_tbl[month][weeks][week + 1] |= TRANS_MARK;
				}*/

				if ((week == SUN) || (calen_tbl[month][weeks][week] & TRANS_MARK))
				{
					calen_tbl[month][weeks][week + 1] |= TRANS_MARK;// 翌日を振り替えにする
				}
				// 祝日カウントを進める 
				holi_cnt++;
			}
			//happymonday
			else {
				if ((week == MON)&&(holidays[month][holi_cnt]<0)&&(holidays[month][holi_cnt]*-1)==mon_cnt)
				{
						calen_tbl[month][mon_cnt][week] |= HOLI_MARK;
						holi_cnt++;

					}

				}
			//  ここに、(3)の例外処理(今日が水曜日以上で、祝日と祝日に挟またら平日は祝日にする処理を入れる)	

			if (week >= WED)
			{
				if ((calen_tbl[month][weeks][week] & HOLI_MARK)&& (calen_tbl[month][weeks][week - 2]&HOLI_MARK))
				{
					calen_tbl[month][weeks][week - 1] |= TRANS_MARK;
					
				}

			}
			if (month == (bmon - 1) && day == bday) {
				calen_tbl[month][mon_cnt][week] |= BIRTH_MARK;
			}
			if (week > SAT) {
				
				week = SUN;
				weeks++;

			}
			day++;
			week++;
		}
	}
	return 0;
}
/*
int prt_holicalen(char calen_tbl[N_MONTH][WEEKS][N_WEEK],int year) {
	for (int month = JAN; month < N_MONTH;month++) {// JAN ～ DEC (月の増加は+1でなく、列数分を増加する)
		for (int weeks = -2; weeks < WEEKS; weeks++) {// 行のループ{　　// -2 ～ 6行 (-2から始める)
			for (int week = 0; week < N_WEEK;week++) {//列のループ{  このループを追加(0～指定された列数)
				if (weeks == -2) {
					printf("%4d年%2d月              ", year,  + 1);
				}//(行が - 2なら)　　年月の表示
	  else if(weeks==-1){
					// (行が - 1なら)　　曜日の表示
	  else {
					for (week == SUN; week < N_WEEK;week++) {// SUN～SAT
		日にちが入っていれば日にちを出力、
		日にちが 0 の場合は日にちの代わりに空白を出力
	  }
	  }
	  列のループが終わったら、改行する
	}
  }
}
*/

