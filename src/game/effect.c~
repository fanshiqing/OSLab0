#include "game.h"
#include "common.h"
#include "string.h"
#include "adt/linklist.h"
#include "device/video.h"
#include "x86/x86.h"

//LINKLIST_IMPL(fly, 10000)

#define STEP_LEN 3 //蛇的大小和蛇每次移动的距离
#define MAXSIZE	100 //蛇的最大长度



typedef enum {left,right,up,down}DIR;
typedef struct LOCATE
{
	int x;
	int y;
}COOR;

//定义食物：坐标与是否被吃
struct FOOD
{
	COOR crd;//食物的坐标
	int flag;//食物的状态：1没吃，0吃了
}food;

struct SNAKE
{
	COOR crd[MAXSIZE];//蛇的每个节点的坐标
	int node;//蛇的当前节点数
	DIR dir;//蛇的前进方向
}snake;

//static fly_t head = NULL;
//static int hit = 0, miss = 0;


//蛇已经成功吃到的食物数目
int
get_eat(void) {
	return snake.node-2;
}
/*
int
get_miss(void) {
	return miss;
}
*/
/*
fly_t
characters(void) {
	return head;
}
*/
/* 在屏幕上创建一个新的字母 */

/*
void
create_new_letter(void) {
	if (head == NULL) {
		head = fly_new(); // 当前没有任何字母，创建新链表 
	} else {
		fly_t now = fly_new();
		fly_insert(NULL, head, now); //插入到链表的头部 
		head = now;
	}
	//字母、初始位置、掉落速度均为随机设定 
	head->x = 0;
	head->y = rand() % (SCR_WIDTH / 8 - 2) * 8 + 8;
	head->v = (rand() % 1000 / 1000.0 + 1) / 2.0;
	head->text = rand() % 26;
	release_key(head->text); //清除过往的按键 
}
*/
//游戏初始化
void Init()
{
	food.flag = 0;
	snake.crd[0].x = 0;
	snake.crd[0].y = 8;
	snake.crd[1].x = 0;
	snake.crd[1].y = 0;
	snake.node = 2;
	snake.dir = right;
}
//在屏幕上随机生成一个食物

bool point_on_snake(int x,int y)
{
	int i;
	for(i =0;i<snake.node;i++)
	{
		if(snake.crd[i].x == x && snake.crd[i].y == y)
			return TRUE;
	}
	return FALSE;
}
//判断蛇头是否出现在身体上
bool point_on_body(int x,int y)
{
	int i;
	for(i=1;i<snake.node;i++)
	{
		if(snake.crd[i].x == x && snake.crd[i].y == y)
			return TRUE;
	}
	return FALSE;
}
void create_new_food(void) {
	if(food.flag == 0)//原来的食物被吃了,则随机生成新的食物
	{
		//food.crd.x = rand()%(SCR_HEIGHT/SNAKELEN)*SNAKELEN + 30;
		//food.crd.x = rand()%(SCR_HEIGHT-30) + 30;
		int x_new,y_new;
		do
		{
			x_new = rand()%(SCR_HEIGHT/8-2)*8 + 8;
			//food.crd.y = rand()%(SCR_WIDTH/SNAKELEN)*SNAKELEN;
			y_new = rand()%(SCR_WIDTH/8-2)*8 + 8;
		}while(point_on_snake(x_new,y_new));
		food.crd.x = x_new;
		food.crd.y = y_new;
		food.flag = 1;
	}
}
//显示蛇
void ShowSnake()
{
	int i;
	char buf[] = "*";
	for(i =0;i<snake.node;i++)
	{
		draw_string(buf,snake.crd[i].x,snake.crd[i].y,15);
	}
}

//显示食物 
void ShowFood()
{	char buf[] = "*";
	draw_string(buf,food.crd.x,food.crd.y,rand()/150);
	//draw_string(buf,20,20,15);
}

//蛇移动
void update_snake_pos(void)
{
	int i;
	//for(i=0;i<snake.node-1;i++)
	for(i=snake.node-1;i>0;i--)
	{
		snake.crd[i].x = snake.crd[i-1].x;
		snake.crd[i].y = snake.crd[i-1].y;
	}
	switch(snake.dir)
	{
		case up:
			snake.crd[0].x -= STEP_LEN;
			break;
		case down:
			snake.crd[0].x += STEP_LEN;
			break;
		case left:
			snake.crd[0].y -= STEP_LEN;
			break;
		case right:
			snake.crd[0].y += STEP_LEN;
			break;
	}
	ShowSnake();//移动一步后显示
}

void JudgeEat(void)
{
	//放宽条件，好像会出问题。。
		
	if((snake.crd[0].x == food.crd.x 
		|| snake.crd[0].x == food.crd.x+1 
		|| snake.crd[0].x == food.crd.x-1 
		|| snake.crd[0].x == food.crd.x+2
		|| snake.crd[0].x == food.crd.x-2) 
		&& (snake.crd[0].y == food.crd.y 
		|| snake.crd[0].y == food.crd.y-1
		||snake.crd[0].y == food.crd.y+1
		||snake.crd[0].y == food.crd.y+2
		||snake.crd[0].y == food.crd.y-2))
	//if(snake.crd[0].x == food.crd.x && snake.crd[0].y == food.crd.y)
	{
		snake.node++;
		snake.crd[snake.node-1].x = food.crd.x;//我去，节点偏移。。
		snake.crd[snake.node-1].y = food.crd.y;
		food.flag = 0;
		//ShowSnake();
	}
}

//判断蛇是否死掉（撞到墙或自己）
void JudgeDie(void)
{
	char *buf;
	if(point_on_body(snake.crd[0].x,snake.crd[0].y))
	{
		buf = "RUN INTO YOURSELF,GAME OVER!";
		draw_string(buf,100,10,30);
		
	}
	if(snake.crd[0].x<0 || snake.crd[0].y<0
		|| snake.crd[0].x>SCR_HEIGHT || snake.crd[0].y > SCR_WIDTH)
	{
		buf = "RUN INTO WALL,GAME OVER!";
		draw_string(buf,100,30,30);
	}
}
/* 逻辑时钟前进1单位 */
/*
void
update_letter_pos(void) {
	fly_t it;
	for (it = head; it != NULL; ) {
		fly_t next = it->_next;
		it->x += it->v; // 根据速度更新位置 
		if (it->x < 0 || it->x + 7.9 > SCR_HEIGHT) {
			if (it->x < 0) hit ++; //从上部飞出屏幕 
			else miss ++; // 从下部飞出屏幕 
			fly_remove(it);
			fly_free(it);
			if (it == head) head = next; //更新链表 
		}
		it = next;
	}
}
*/
//改变蛇的运动方向
void ChangeDir()
{
	disable_interrupt();
	//寻找已经按下的键，若有多个键按下，处理优先级以此为上下左右
	int i;
	for(i=0;i<4;i++)
	{
		if(query_key(i))
			switch(i)
			{
				case 0:snake.dir = up;break;
				case 1:snake.dir = down;break;
				case 2:snake.dir = left;break;
				case 3:snake.dir = right;break;
			}
		release_key(i);
	}	
	enable_interrupt();
}	
/* 更新按键 */
/*
bool
update_keypress(void) {
	fly_t it, target = NULL;
	float min = -100;

	disable_interrupt();
	// 寻找相应键已被按下、最底部且未被击中的字符 
	for (it = head; it != NULL; it = it->_next) {
		assert(it->text >= 0 && it->text < 26);
		if (it->v > 0 && it->x > min && query_key(it->text)) {
			min = it->x;
			target = it;
		}
	}
	//如果找到则更新相应数据 
	if (target != NULL) {
		release_key(target->text);
		target->v = -3; // 速度改为向上 
		return TRUE;
	}
	enable_interrupt();

	return FALSE;
}
*/





