#include "game.h"
#include "string.h"
#include "device/video.h"

//static int count_of_loop = 0 ;

/* 绘制屏幕上的内容。
 * 注意程序在绘图之前调用了prepare_buffer，结束前调用了display_buffer。
 * prepare_buffer会准备一个空白的绘图缓冲区，display_buffer则会将缓冲区绘制到屏幕上，
 * draw_pixel或draw_string绘制的内容将保存在缓冲区内(暂时不会显示在屏幕上)，调用
 * display_buffer后才会显示。
*/
void
redraw_screen() {
	//count_of_loop++;
	//fly_t it;
	//const char *hit, *miss;
	const char* eat;
	
	prepare_buffer(); /* 准备缓冲区 */


	/* 绘制每个字符 */
	/*
	for (it = characters(); it != NULL; it = it->_next) {
		static char buf[2];
		//buf[0] = it->text + 'A'; buf[1] = 0;
		buf[0] = '[';//这样的话已经能显示雪花啦！
		buf[1] = ']';
		//draw_string(buf, it->x, it->y, rand()/150);//实现了色彩多变的颜色
		ShowSnake();
		ShowFood();
	}
	*/
	
	//char buf[] = "---------------------------------------";
	//draw_string(buf,30,0,15);
	//if(count_of_loop % 2 == 0)
	//{
		ShowSnake();
		ShowFood();
	//}
	/* 绘制命中数、miss数、最后一次按键扫描码和fps */
	//draw_string(itoa(last_key_code()), SCR_HEIGHT - 8, 0, 48);
	//
	//绘制迟到的食物数目
	
	char buf[] = "SCORE:";
	eat = itoa(get_eat());
	
	draw_string(eat, 0, SCR_WIDTH - strlen(eat) * 8, 10);
	draw_string(buf, 0, 256, 10);
	//miss = itoa(get_miss());
	//draw_string(miss, SCR_HEIGHT - 8, SCR_WIDTH - strlen(miss) * 8, 12);
	//draw_string(itoa(get_fps()), 0, 0, 14);
	//draw_string("FPS", 0, strlen(itoa(get_fps())) * 8, 14);
	//draw_string("fanshiqing", 0, 0, 14);

	//char buf2[] = "YOU HAVE RUN INTO YOUSLEF,GAME OVER!";
	//draw_string(buf2,100,10,30);

	display_buffer(); /* 绘制缓冲区 */
}





















