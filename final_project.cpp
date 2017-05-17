#include<simplecpp>
const int lx=50, ly=50, rc=9, nx=8, ny=8, xo=300, yo=200;
int colour_red(int player_code)					//function for setting the red value of the colour
{
	if(player_code==1)
	{
		return 255; 
	}
	if(player_code==2)
	{
		return 0;
	}
	if(player_code==3)
	{
		return 0;
	}
	if(player_code==4)
	{
		return 255;
	}
	if(player_code==5)
	{
		return 139;
	}
	if(player_code==6)
	{
		return 210;
	}
	if(player_code==7)
	{
		return 0;
	}
	if(player_code==8)
	{
		return 255;
	}
	else return 0;
}

int colour_green(int player_code)				//function for setting the green value of the colour
{
	if(player_code==1)
	{
		return 0; 
	}
	if(player_code==2)
	{
		return 255;
	}
	if(player_code==3)
	{
		return 0;
	}
	if(player_code==4)
	{
		return 215;
	}
	if(player_code==5)
	{
		return 0;
	}
	if(player_code==6)
	{
		return 105;
	}
	if(player_code==7)
	{
		return 255;
	}
	if(player_code==8)
	{
		return 0;
	}
	else return 0;
}

int colour_blue(int player_code)				//function for setting the blue value of the colour
{
	if(player_code==1)
	{
		return 0; 
	}
	if(player_code==2)
	{
		return 0;
	}
	if(player_code==3)
	{
		return 255;
	}
	if(player_code==4)
	{
		return 0;
	}
	if(player_code==5)
	{
		return 139;
	}
	if(player_code==6)
	{
		return 30;
	}
	if(player_code==7)
	{
		return 255;
	}
	if(player_code==8)
	{
		return 255;
	}
	else return 0;
}

class Block						//Defining the class block
{
	public:
	Rectangle r;
	Circle c[9];					//Array for the constituting circles
	int count;					//Count of activated orbs
	int player;					//Code of the player occupying the block
	
	Block()						//constructor
	{
		count=0;
		player=0;
	}
	
	void orient(Block b[nx][ny])			//for creating the grid
	{
		int i,j,k,l,m=0, x=xo, y=yo;
		for(i=0;i<ny;i++)
		{
			for(j=0;j<nx;j++)
			{
				b[i][j].r.reset(x,y,lx,ly);
				b[i][j].r.setColor(COLOR(0,0,0));
				b[i][j].c[8].reset(x,y,rc);
				b[i][j].c[8].setFill();
				b[i][j].c[8].hide();
				for(k=0;k<2;k++)
				{
					for(l=0;l<2;l++)
					{
						b[i][j].c[m].reset(x-7.5+15*l,y-7.5+15*k,rc);
						b[i][j].c[m].setFill();
						b[i][j].c[m].hide();
						b[i][j].c[m+4].reset(x-7.5+15*l,y-7.5+15*k,rc);
						b[i][j].c[m+4].setFill();
						b[i][j].c[m+4].hide();
						m++;
					}
				}
				m=0;
				x+=50;
			}
			y+=50;
			x=300;
		}
	}
	void exit(Block b[nx][ny])			//for hiding the grid and resetting the attributes
	{
		for(int i=ny-1;i>=0;i--)
		{
			for(int j=nx-1;j>=0;j--)
			{
				b[i][j].r.hide();
				b[i][j].player=0;
				b[i][j].count=0;
				for(int k=0;k<4;k++)
				{
					b[i][j].c[k].hide();
				}
			}
		}
	}
	void up(int player_code)			//for animating the upward movement of the orb
	{
		c[8].setColor(COLOR(colour_red(player_code),colour_green(player_code),colour_blue(player_code)));
		c[8].show();
		repeat(25)
		{
			c[8].move(0,-2);
		}
		c[8].hide();
		c[8].move(0,50);
	}
	void right(int player_code)		//for animating the right movement of the orb
	{
		c[8].setColor(COLOR(colour_red(player_code),colour_green(player_code),colour_blue(player_code)));
		c[8].show();
		repeat(25)
		{
			c[8].move(2,0);
		}
		c[8].hide();
		c[8].move(-50,0);
	}
	void down(int player_code)			//for animating the downward movement of the orb
	{
		c[8].setColor(COLOR(colour_red(player_code),colour_green(player_code),colour_blue(player_code)));
		c[8].show();
		repeat(25)
		{
			c[8].move(0,2);
		}
		c[8].hide();
		c[8].move(0,-50);
	}
	void left(int player_code)			//for animating the left movement of the orb
	{
		c[8].setColor(COLOR(colour_red(player_code),colour_green(player_code),colour_blue(player_code)));
		c[8].show();
		repeat(25)
		{
			c[8].move(-2,0);
		}
		c[8].hide();
		c[8].move(50,0);
	}
};

void blast(int case_, Block b[nx][ny],int index_row, int index_coloumn);	//declaring the function blast
void scan(int case_,Block b[nx][ny],int index_row, int index_coloumn)	//declaring the function scan which checks for saturation of the parameterized cell
{
	if(case_==1||case_==2||case_==3||case_==4)		//differentiating the cases
	{
		if(b[index_row-1][index_coloumn-1].count>=2){blast(case_,b,index_row,index_coloumn);}
	}
	else if(case_==5||case_==6||case_==7||case_==8)
	{
		if(b[index_row-1][index_coloumn-1].count>=3){blast(case_,b,index_row,index_coloumn);}
	}
	else if(case_==9)
	{
		if(b[index_row-1][index_coloumn-1].count>=4){blast(case_,b,index_row,index_coloumn);}
	}

}
int case2(int i, int j)						//for returning the case type of the parameterized cell
{
	if((i==1)&&(j==1)){return 1;}
	else if((i==1)&&(j==ny)){return 2;}
	else if((i==nx)&&(j==ny)){return 3;}
	else if((i==nx)&&(j==1)){return 4;}
	else if((i==1)&&(j<ny)&&(j>1)){return 5;}
	else if((i>1)&&(i<nx)&&(j==ny)){return 6;}
	else if((i==nx)&&(j<ny)&&(j>1)){return 7;}
	else if((i>1)&&(i<nx)&&(j==1)){return 8;}
	else {return 9;}
}


void show(Block b[nx][ny],int index_row,int index_coloumn);	//declaring show function
void hide(Block b[nx][ny],int index_row,int index_coloumn)	//hides the circles of the cell
{
	for(int s=0;s<8;s++)
	{
		b[index_row-1][index_coloumn-1].c[s].hide();
	}
	show(b,index_row,index_coloumn);	

}
void show(Block b[nx][ny],int index_row,int index_coloumn)	//updates and shows the status of the parameterized cell
{
	for(int s=0;s<b[index_row-1][index_coloumn-1].count&&s<8;s++)
	{
		int player_code=b[index_row-1][index_coloumn-1].player;
		b[index_row-1][index_coloumn-1].c[s].show();
		b[index_row-1][index_coloumn-1].c[s].setColor(COLOR(colour_red(player_code),colour_green(player_code),colour_blue(player_code)));
	}	

}
bool checkwin(Block b[nx][ny]);					//declaring checkwin
void blast(int case_, Block b[nx][ny],int index_row, int index_coloumn)		//the blast function which increases the count of neighbouring cells,updates the count of the current cell and calls the scan function for adjoint cells.
{
	if(checkwin(b)){wait(2);return;}			//checking the win condition(required for cases of consecutive blasts, to avoid running into infinite loop)
	if(case_==1 || case_==2 || case_==3 || case_==4)
	{
		b[index_row-1][index_coloumn-1].count-=2;			
		hide(b,index_row,index_coloumn);
	}
	if(case_==5 || case_==6 || case_==7 || case_==8)
	{
		b[index_row-1][index_coloumn-1].count-=3;			
		hide(b,index_row,index_coloumn);
	}
	if(case_==1)
	{
		b[0][1].player=b[0][0].player;b[0][1].count++;b[0][0].right(b[0][0].player);show(b,1,2);
		b[1][0].player=b[0][0].player;b[1][0].count++;b[0][0].down(b[0][0].player);show(b,2,1);
		if(b[index_row-1][index_coloumn-1].count==0)b[index_row-1][index_coloumn-1].player=0;
		scan(5,b,1,2);scan(8,b,2,1);
		
	}
	else if(case_==2)
	{
		b[0][ny-2].player=b[index_row-1][index_coloumn-1].player;b[0][ny-2].count++;b[index_row-1][index_coloumn-1].left(b[index_row-1][index_coloumn-1].player);show(b,1,ny-1);
		b[1][ny-1].player=b[index_row-1][index_coloumn-1].player;b[1][ny-1].count++;;b[index_row-1][index_coloumn-1].down(b[index_row-1][index_coloumn-1].player);show(b,2,ny);
		if(b[index_row-1][index_coloumn-1].count==0)b[index_row-1][index_coloumn-1].player=0;
		scan(5,b,1,ny-1);
		scan(6,b,2,ny);
		
	}
	else if(case_==3)
	{
		b[nx-1][ny-2].player=b[index_row-1][index_coloumn-1].player;b[nx-1][ny-2].count++;b[index_row-1][index_coloumn-1].left(b[index_row-1][index_coloumn-1].player);show(b,nx,ny-1);
		b[nx-2][ny-1].player=b[index_row-1][index_coloumn-1].player;b[nx-2][ny-1].count++;b[index_row-1][index_coloumn-1].up(b[index_row-1][index_coloumn-1].player);show(b,nx-1,ny);
		if(b[index_row-1][index_coloumn-1].count==0)b[index_row-1][index_coloumn-1].player=0;
		scan(7,b,nx,ny-1);
		scan(6,b,nx-1,ny);
		
	}
	else if(case_==4)
	{
		b[nx-2][0].player=b[index_row-1][index_coloumn-1].player;b[nx-2][0].count++;b[index_row-1][index_coloumn-1].up(b[index_row-1][index_coloumn-1].player);show(b,nx-1,1);
		b[nx-1][1].player=b[index_row-1][index_coloumn-1].player;b[nx-1][1].count++;b[index_row-1][index_coloumn-1].right(b[index_row-1][index_coloumn-1].player);show(b,nx,2);
		if(b[index_row-1][index_coloumn-1].count==0)b[index_row-1][index_coloumn-1].player=0;
		scan(8,b,nx-1,1);
		scan(7,b,nx,2);
		
	}
	else if(case_==5)
	{
		b[0][index_coloumn].player=b[index_row-1][index_coloumn-1].player;b[0][index_coloumn].count++;b[index_row-1][index_coloumn-1].right(b[index_row-1][index_coloumn-1].player);show(b,1,index_coloumn+1);
		b[0][index_coloumn-2].player=b[index_row-1][index_coloumn-1].player;b[0][index_coloumn-2].count++;b[index_row-1][index_coloumn-1].left(b[index_row-1][index_coloumn-1].player);show(b,1,index_coloumn-1);
		b[1][index_coloumn-1].player=b[index_row-1][index_coloumn-1].player;b[1][index_coloumn-1].count++;b[index_row-1][index_coloumn-1].down(b[index_row-1][index_coloumn-1].player);show(b,2,index_coloumn);
		if(b[index_row-1][index_coloumn-1].count==0)b[index_row-1][index_coloumn-1].player=0;
		scan(case2(1,index_coloumn+1),b,1,index_coloumn+1);
		scan(case2(1,index_coloumn-1),b,1,index_coloumn-1);
		scan(9,b,2,index_coloumn);
		
	}
	else if(case_==6)
	{
		b[index_row][ny-1].player=b[index_row-1][index_coloumn-1].player;b[index_row][ny-1].count++;b[index_row-1][index_coloumn-1].down(b[index_row-1][index_coloumn-1].player);show(b,index_row+1,ny);
		b[index_row-2][ny-1].player=b[index_row-1][index_coloumn-1].player;b[index_row-2][ny-1].count++;b[index_row-1][index_coloumn-1].up(b[index_row-1][index_coloumn-1].player);show(b,index_row-1,ny);
		b[index_row-1][ny-2].player=b[index_row-1][index_coloumn-1].player;b[index_row-1][ny-2].count++;b[index_row-1][index_coloumn-1].left(b[index_row-1][index_coloumn-1].player);show(b,index_row,ny-1);
		if(b[index_row-1][index_coloumn-1].count==0)b[index_row-1][index_coloumn-1].player=0;
		scan(case2(index_row+1,ny),b,index_row+1,ny);
		scan(case2(index_row-1,ny),b,index_row-1,ny);
		scan(9,b,index_row,ny-1);
		
	}
	else if(case_==7)
	{
		b[nx-1][index_coloumn].player=b[index_row-1][index_coloumn-1].player;b[nx-1][index_coloumn].count++;b[index_row-1][index_coloumn-1].right(b[index_row-1][index_coloumn-1].player);show(b,nx,index_coloumn+1);
		b[nx-1][index_coloumn-2].player=b[index_row-1][index_coloumn-1].player;b[nx-1][index_coloumn-2].count++;b[index_row-1][index_coloumn-1].left(b[index_row-1][index_coloumn-1].player);show(b,nx,index_coloumn-1);
		b[nx-2][index_coloumn-1].player=b[index_row-1][index_coloumn-1].player;b[nx-2][index_coloumn-1].count++;b[index_row-1][index_coloumn-1].up(b[index_row-1][index_coloumn-1].player);show(b,nx-1,index_coloumn);
		if(b[index_row-1][index_coloumn-1].count==0)b[index_row-1][index_coloumn-1].player=0;
		scan(case2(nx,index_coloumn+1),b,nx,index_coloumn+1);
		scan(case2(nx,index_coloumn-1),b,nx,index_coloumn-1);
		scan(9,b,nx-1,index_coloumn);
		
	}
	else if(case_==8)
	{
		b[index_row][0].player=b[index_row-1][index_coloumn-1].player;b[index_row][0].count++;b[index_row-1][index_coloumn-1].down(b[index_row-1][index_coloumn-1].player);show(b,index_row+1,1);
		b[index_row-2][0].player=b[index_row-1][index_coloumn-1].player;b[index_row-2][0].count++;b[index_row-1][index_coloumn-1].up(b[index_row-1][index_coloumn-1].player);show(b,index_row-1,1);
		b[index_row-1][1].player=b[index_row-1][index_coloumn-1].player;b[index_row-1][1].count++;b[index_row-1][index_coloumn-1].right(b[index_row-1][index_coloumn-1].player);show(b,index_row,2);
		if(b[index_row-1][index_coloumn-1].count==0)b[index_row-1][index_coloumn-1].player=0;
		scan(case2(index_row+1,1),b,index_row+1,1);
		scan(9,b,index_row,2);
		scan(case2(index_row-1,1),b,index_row-1,1);
		
	}
	else if(case_==9)
	{
		b[index_row-1][index_coloumn-1].count-=4;			
		hide(b,index_row,index_coloumn);
		b[index_row-1][index_coloumn].player=b[index_row-1][index_coloumn-1].player;b[index_row-1][index_coloumn].count++;b[index_row-1][index_coloumn-1].right(b[index_row-1][index_coloumn-1].player);show(b,index_row,index_coloumn+1);
		b[index_row-1][index_coloumn-2].player=b[index_row-1][index_coloumn-1].player;b[index_row-1][index_coloumn-2].count++;b[index_row-1][index_coloumn-1].left(b[index_row-1][index_coloumn-1].player);show(b,index_row,index_coloumn-1);
		b[index_row][index_coloumn-1].player=b[index_row-1][index_coloumn-1].player;b[index_row][index_coloumn-1].count++;b[index_row-1][index_coloumn-1].down(b[index_row-1][index_coloumn-1].player);show(b,index_row+1,index_coloumn);
		b[index_row-2][index_coloumn-1].player=b[index_row-1][index_coloumn-1].player;b[index_row-2][index_coloumn-1].count++;b[index_row-1][index_coloumn-1].up(b[index_row-1][index_coloumn-1].player);show(b,index_row-1,index_coloumn);
		if(b[index_row-1][index_coloumn-1].count==0)b[index_row-1][index_coloumn-1].player=0;
		scan(case2(index_row,index_coloumn+1),b,index_row,index_coloumn+1);
		scan(case2(index_row,index_coloumn-1),b,index_row,index_coloumn-1);
		scan(case2(index_row+1,index_coloumn),b,index_row+1,index_coloumn);
		scan(case2(index_row-1,index_coloumn),b,index_row-1,index_coloumn);
		
	}
	
}



int Case(int& i, int& j,unsigned int Coordinate)		//returns the row and coloumn number of the selected cell on the basis of value of the getclick function
{
	float xcoord=Coordinate/65536, ycoord=Coordinate%65536;
	if((xcoord>xo-lx/2)&&(xcoord<xo-lx/2+nx*lx)&&(ycoord>yo-ly/2)&&(ycoord<yo-ly/2+ny*ly))	//click inside the grid
	{
		for(int z1=0;z1<nx;z1++)
		{
			if((xcoord>=(xo-lx/2+z1*lx)) && (xcoord<(xo-lx/2+(z1+1)*lx)))
			{
				j=z1+1;break;
			}
		}
		for(int z2=0;z2<ny;z2++)
		{
			if((ycoord>=(yo-ly/2+z2*ly)) && (ycoord<=(yo-ly/2+(z2+1)*ly)))
			{
				i=z2+1;break;
			}
		}
	
		if((i==1)&&(j==1)){return 1;}
		else if((i==1)&&(j==ny)){return 2;}
		else if((i==nx)&&(j==ny)){return 3;}
		else if((i==nx)&&(j==1)){return 4;}
		else if((i==1)&&(j<ny)&&(j>1)){return 5;}
		else if((i>1)&&(i<nx)&&(j==ny)){return 6;}
		else if((i==nx)&&(j<ny)&&(j>1)){return 7;}
		else if((i>1)&&(i<nx)&&(j==1)){return 8;}
		else {return 9;}
	}
	else if(xcoord>=900-(textWidth("Back"))/2 && xcoord<=900+(textWidth("Back"))/2 && ycoord>=600-(textHeight())/2 && ycoord<=600+(textHeight())/2){return 23;}			//click on the "back" button
	else return 22;				//click elsewhere
	
}

bool checkwin(Block b[nx][ny])				//checks if the game is won
{
	bool win=true,variable_found=false;int variable=0;
	for(int i=0;i<nx;i++)
	{
		for(int j=0;j<ny;j++)
		{
			if(variable_found==false&&b[i][j].player!=0){variable=b[i][j].player;variable_found=true;}
			win=(b[i][j].player==variable||b[i][j].player==0);
			if(win==false){break;}			
		}
		if(win==false){break;}
	}
	return win;
}

void player_present(Block b[nx][ny],int& current_player,int& r, int num)	//checks if the player is still in the game
{
	bool player_found=false;
	for(int i=0;i<nx;i++)
	{
		for(int j=0;j<ny;j++)
		{
			if(b[i][j].player==current_player){player_found=true;break;}
		}
		if(player_found==true){break;}
	}
	
	if(player_found==false){current_player=((current_player)%num)+1;r++;player_present(b,current_player,r,num);}
}

bool checkmove(Block b[nx][ny],int index_row, int index_coloumn, int curr_player)	//checks if the move is legal
{
	bool is_valid=false;
	if(b[index_row-1][index_coloumn-1].player==curr_player ||b[index_row-1][index_coloumn-1].player==0)
	{
		is_valid=true;
	}
	else {is_valid=false;}
	return is_valid;
	
}

main_program
{
	initCanvas("Main Game",1000,1000);
	Text i1(0,300,"A project by");					//intro
	repeat(500)
	{
		i1.move(1,0);
	}
	Text i2(1000,350,"Pranjal & Anmol");
	repeat(500)
	{
		i2.move(-1,0);
	}
	wait(1);
	i1.hide();i2.hide();
	Text i3(500,0,"Chain Reaction");
	repeat(300)
	{
		i3.move(0,1);
	}
	wait(1);
	i3.hide();
	Text i4(500,300,"Loading...");
	Block b[nx][ny];					//creating required objects
	Block c;
	Text p1,g1,l1,l2,b1,e[8];
	Circle f[8];
	int r,current_player;
	bool win;
	i4.hide();
	a:
	Text t1(500,300,"Play");				//welcome screen
	Text t2(500,350,"Instructions");
	Text t3(500,400,"Quit");
	bool click=false;
	unsigned int z,choice=0;
	float x,y;
	int num=0;
	while(click==false)
	{
		z=getClick();
		x=z/65536;
		y=z%65536;
		if(x>=500-(textWidth("Play"))/2 && x<=500+(textWidth("Play"))/2 && y>=300-(textHeight())/2 && y<=300+(textHeight())/2)
		{
			click=true;
			choice=1;
		}			//click on the "play" button
		if(x>=500-(textWidth("Instructions"))/2 && x<=500+(textWidth("Instructions"))/2 && y>=350-(textHeight())/2 && y<=350+(textHeight())/2)
		{
			click=true;
			choice=2;
		}	//click on "instructions" button
		if(x>=500-(textWidth("Quit"))/2 && x<=500+(textWidth("Quit"))/2 && y>=400-(textHeight())/2 && y<=400+(textHeight())/2)
		{
			click=true;
			choice=3;
		}		//click on "quit" button
	}
	click=false;
	t1.hide();
	t3.hide();
	t2.hide();
	if(choice==1)		//proceed with play option
	{
		Text t11(500,250,"Select the number of players : ");
		Text n2(350,300,"2");Text n3(400,300,"3");Text n4(450,300,"4");Text n5(500,300,"5");Text n6(550,300,"6");Text n7(600,300,"7");Text n8(650,300,"8");
		Text t12(900,600,"Back");
		while(click==false)			//click for selecting the number of players
		{
			z=getClick();
			x=z/65536;
			y=z%65536;			
			if(x>=350-(textWidth("2"))/2 && x<=350+(textWidth("2"))/2 && y>=300-(textHeight())/2 && y<=300+(textHeight())/2)
			{
				click=true;
				num=2;
			}
			if(x>=400-(textWidth("3"))/2 && x<=400+(textWidth("3"))/2 && y>=300-(textHeight())/2 && y<=300+(textHeight())/2)
			{
				click=true;
				num=3;
			}
			if(x>=450-(textWidth("4"))/2 && x<=450+(textWidth("4"))/2 && y>=300-(textHeight())/2 && y<=300+(textHeight())/2)
			{
				click=true;
				num=4;
			}
			if(x>=500-(textWidth("5"))/2 && x<=500+(textWidth("5"))/2 && y>=300-(textHeight())/2 && y<=300+(textHeight())/2)
			{
				click=true;
				num=5;
			}
			if(x>=550-(textWidth("6"))/2 && x<=550+(textWidth("6"))/2 && y>=300-(textHeight())/2 && y<=300+(textHeight())/2)
			{
				click=true;
				num=6;
			}
			if(x>=600-(textWidth("7"))/2 && x<=600+(textWidth("7"))/2 && y>=300-(textHeight())/2 && y<=300+(textHeight())/2)
			{
				click=true;
				num=7;
			}
			if(x>=650-(textWidth("8"))/2 && x<=650+(textWidth("8"))/2 && y>=300-(textHeight())/2 && y<=300+(textHeight())/2)
			{
				click=true;
				num=8;
			}
			if(x>=900-(textWidth("Back"))/2 && x<=900+(textWidth("Back"))/2 && y>=600-(textHeight())/2 && y<=600+(textHeight())/2)
			{
				click=true;
				choice=0;
				t11.hide();t12.hide();n2.hide();n3.hide();n4.hide();n5.hide();n6.hide();n7.hide();n8.hide();
				goto a;		//goes back to the welcome screen
			}
		}
		t11.hide();t12.hide();n2.hide();n3.hide();n4.hide();n5.hide();n6.hide();n7.hide();n8.hide();
	}
	if(choice==2)				//instruction page
	{
		
		Text t21(500,250,"A strategy game for 2 to 8 players.");
		Text t22(500,300,"The objective of Chain Reaction is to take control of the board by eliminating your opponents' orbs.");
		Text t23(500,350,"Players take it in turns to place their orbs in a cell. Once a cell has reached critical mass the orbs");
		Text t24(500,375,"explode into the surrounding cells adding an extra orb and claiming the cell for the player.");
		Text t25(500,400,"A player may only place their orbs in a blank cell or a cell that contains orbs of their own colour.");
		Text t26(500,425,"As soon as a player looses all their orbs they are out of the game.");
		Text t27(900,600,"Back");
		while(click==false)
		{
			z=getClick();
			x=z/65536;
			y=z%65536;
			if(x>=900-(textWidth("Back"))/2 && x<=900+(textWidth("Back"))/2 && y>=600-(textHeight())/2 && y<=600+(textHeight())/2)
			{
				click=true;
				choice=0;
				t21.hide();t22.hide();t23.hide();t24.hide();t25.hide();t26.hide();t27.hide();
				goto a;
			}
		}
	}
	if(choice==3)				// to quit
	{
		return 0;
	}	
	win=false;
	r=0;					//dummy variable used for calculating current player's code
	current_player=(r%num)+1;
	c.orient(b);				//creating the grid
	for(int i=0;i<8;i++)			//to display the index of players along with their colour codes
	{
		f[i].setColor(COLOR(colour_red(i+1),colour_green(i+1),colour_blue(i+1)));
		f[i].setFill();
		f[i].reset(75,225+i*50,rc);
		switch(i+1)
		{
			case 1:e[i].reset(150,225+i*50,"Player 1");break;
			case 2:e[i].reset(150,225+i*50,"Player 2");break;
			case 3:e[i].reset(150,225+i*50,"Player 3");break;
			case 4:e[i].reset(150,225+i*50,"Player 4");break;
			case 5:e[i].reset(150,225+i*50,"Player 5");break;
			case 6:e[i].reset(150,225+i*50,"Player 6");break;
			case 7:e[i].reset(150,225+i*50,"Player 7");break;
			case 8:e[i].reset(150,225+i*50,"Player 8");break;	
		}
	}
	b1.reset(900,600,"Back");
	while(win==false)		
	{
		current_player=(r%num)+1;		//since the count of players starts from 1(to 8)
		if(r>num)
		{
			player_present(b,current_player,r,num);	//checks if the current player is still in the game, otherwise shifts the control to the next player in the line
		}

		for(int i=0;i<nx;i++)			//change the colour of the grid to the colour of present player
		{
			for(int z=0;z<ny;z++)
			{
				b[i][z].r.setColor(COLOR(colour_red(current_player),colour_green(current_player),colour_blue(current_player)));
			}
		
		}
		cout<<"Next move: Player "<<current_player<<endl;
		int i=1,j=1,case_1=22;
		unsigned int z;
		p:
		if(case_1==23)								
		{
			c.exit(b);				//to proceed with "back" option, hides and resets the grid
			choice=0;num=0;
			b1.hide();
			for(int i=0;i<8;i++)			//to hide the player index
			{
				f[i].hide();
				e[i].hide();
			}
			goto a;
		}
		while(case_1==22)				//for getting a click inside the grid or in the "back" button
		{
			z=getClick();
			case_1=Case(i,j,z);
			if(case_1==22){cout<<"Invalid move. Player "<<current_player<<", please play again.\n";}
			else if(case_1==23){goto p;}
		}
		if(checkmove(b,i,j,current_player)==true)	//continue only if the move is valid
		{
			b[i-1][j-1].player=current_player;
			b[i-1][j-1].count++;			
			show(b,i,j);			
			scan(case_1,b,i,j);
			r++;					//to pass control to the next player
		}
		else {cout<<"Invalid move. Player "<<current_player<<" play again. "<<endl;}
		if(r>num)win=checkwin(b);			//to exit the loop if game is won
	}
	b1.hide();						//hide the grid when the game is won
	for(int i=0;i<8;i++)					//hide the player index
	{
		f[i].hide();
		e[i].hide();
	}
	c.exit(b);
	click=false;
	switch(current_player)				//display win status
	{
		case 1:p1.reset(500,300,"Player 1 wins");g1.reset(500,400,"( click to continue )");while(click==false){z=getClick();if(z>0)click=true;}p1.hide();g1.hide();break;
		case 2:p1.reset(500,300,"Player 2 wins");g1.reset(500,400,"( click to continue )");while(click==false){z=getClick();if(z>0)click=true;}p1.hide();g1.hide();break;
		case 3:p1.reset(500,300,"Player 3 wins");g1.reset(500,400,"( click to continue )");while(click==false){z=getClick();if(z>0)click=true;}p1.hide();g1.hide();break;
		case 4:p1.reset(500,300,"Player 4 wins");g1.reset(500,400,"( click to continue )");while(click==false){z=getClick();if(z>0)click=true;}p1.hide();g1.hide();break;
		case 5:p1.reset(500,300,"Player 5 wins");g1.reset(500,400,"( click to continue )");while(click==false){z=getClick();if(z>0)click=true;}p1.hide();g1.hide();break;
		case 6:p1.reset(500,300,"Player 6 wins");g1.reset(500,400,"( click to continue )");while(click==false){z=getClick();if(z>0)click=true;}p1.hide();g1.hide();break;
		case 7:p1.reset(500,300,"Player 7 wins");g1.reset(500,400,"( click to continue )");while(click==false){z=getClick();if(z>0)click=true;}p1.hide();g1.hide();break;
		case 8:p1.reset(500,300,"Player 8 wins");g1.reset(500,400,"( click to continue )");while(click==false){z=getClick();if(z>0)click=true;}p1.hide();g1.hide();break;

	}
	l1.reset(500,200,"Play Again");
	l2.reset(500,400,"Quit");
	click=false;
	while(click==false)			//displays the screen after the game is won
	{
		z=getClick();
		x=z/65536;
		y=z%65536;
		if(x>=500-(textWidth("Play Again"))/2 && x<=500+(textWidth("Play Again"))/2 && y>=200-(textHeight())/2 && y<=200+(textHeight())/2)
		{
			click=true;
			choice=0;num=0;
			l1.hide();l2.hide();
			goto a;
		}
		if(x>=500-(textWidth("Quit"))/2 && x<=500+(textWidth("Quit"))/2 && y>=400-(textHeight())/2 && y<=400+(textHeight())/2)
		{
			click=true;
			l1.hide();l2.hide();
		}	
	}
}
