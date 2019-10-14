#include"sheng_ming.h"

//-----------------------------------------------------------------------------------------------------------

void guan_li_xi_tong()
{
	bool opt = true;        //是否循环的一个标志

	while (opt == true)
	{
		system("cls"); //清屏
		//菜单列表
		cout << "\n";
		cout << "\n\t\t********************职工工资管理系统********************\n";
		cout << "\t\t*                                                      *\n";
		cout << "\t\t*                                                      *\n";
		cout << "\t\t*   1.职工基本信息管理   2.部门管理   3.职工工资管理   *\n";
		cout << "\t\t*                                                      *\n";
		cout << "\t\t*                                                      *\n";
		cout << "\t\t*         4.岗位及岗位等级管理     5.退 出             *\n";
		cout << "\t\t*                                                      *\n";
		cout << "\t\t*                                                      *\n";
		cout << "\t\t********************************************************\n";

		//接收输入选择
		cout << "\n\t\t请选择功能数字：";
		char x[100];
		cin >> x;

		//判断用户的选择
		switch (x[0])
		{
		case '1':
			system("cls");
			opt = zhi_gong_ji_ben_xin_xi_guan_li();   //职工基本信息管理（二级菜单）
			break;
		case '2':
			system("cls");
			opt = bu_men_guan_li();     //部门管理（二级菜单）
			break;
		case '3':
			system("cls");
			opt = zhi_gong_gong_zi_guan_li();  //职工工资管理（二级菜单）
			break;
		case '4':
			system("cls");
			opt = gang_wei_ji_gang_wei_deng_ji_guan_li();  //岗位及岗位等级管理（二级菜单）
			break;
		case '5':
			system("cls");
			opt = false;        //把标志位为假，就退出了循环
			break;
		default:
			cout << "\n\t\t非法输入，将返回目录!\n";
			cout << "\n\t(任意键返回)"; system("pause");
		}
	}
}