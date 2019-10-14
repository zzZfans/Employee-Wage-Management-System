#include"sheng_ming.h"

//-----------------------------------------------------------------------------------------------------------

bool gang_wei_ji_gang_wei_deng_ji_guan_li()
{
	gang_wei gang_wei_head;
	gang_wei_head.next = NULL;

	gang_wei gang_wei_p;
	gang_wei_p.next = NULL;

	gang_wei_f_in(&gang_wei_head, &gang_wei_p);

	gang_wei_deng_ji gang_wei_deng_ji_head;
	gang_wei_deng_ji_head.next = NULL;

	gang_wei_deng_ji gang_wei_deng_ji_p;
	gang_wei_deng_ji_p.next = NULL;

	gang_wei_deng_ji_f_in(&gang_wei_deng_ji_head, &gang_wei_deng_ji_p);

qi_dian:

	system("cls"); //清屏

	cout << "\n";
	cout << "\n\t\t*******************岗位及岗位等级管理*******************\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t*       1.增加岗位信息            5.增加岗位等级       *\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t*       2.修改岗位信息            6.修改岗位等级       *\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t*       3.删除岗位信息            7.删除岗位等级       *\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t*       4.浏览岗位信息            8.浏览岗位等级       *\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t*       9.返回                    0.退出               *\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t********************************************************\n";

	cout << "\n\t\t请选择功能数字：";

	char x[100];

	cin >> x;      //接受输入

	switch (x[0])
	{
	case '1':
		gang_wei_in(&gang_wei_head, &gang_wei_p);
		goto qi_dian;

	case '2':
		gang_wei_xiu_gai(&gang_wei_head);
		goto qi_dian;

	case '3':
		gang_wei_del(&gang_wei_head);
		goto qi_dian;

	case '4':
		gang_wei_put(&gang_wei_head);
		cout << "\n\t(任意键返回)"; system("pause");
		goto qi_dian;

	case '5':
		gang_wei_deng_ji_in(&gang_wei_deng_ji_head, &gang_wei_deng_ji_p);
		goto qi_dian;

	case '6':
		gang_wei_deng_ji_xiu_gai(&gang_wei_deng_ji_head);
		goto qi_dian;

	case '7':
		gang_wei_deng_ji_del(&gang_wei_deng_ji_head);
		goto qi_dian;

	case '8':
		gang_wei_deng_ji_put(&gang_wei_deng_ji_head);
		cout << "\n\t(任意键返回)"; system("pause");
		goto qi_dian;

	case '9':
		gang_wei_dong_tai_hui_shou(&gang_wei_head);
		gang_wei_deng_ji_dong_tai_hui_shou(&gang_wei_deng_ji_head);
		return true;

	case '0':
		gang_wei_dong_tai_hui_shou(&gang_wei_head);
		gang_wei_deng_ji_dong_tai_hui_shou(&gang_wei_deng_ji_head);
		return false;


	default:
		cout << "\n\t\t非法输入,将返回目录!\n";
		cout << "\n\t(任意键返回)"; system("pause");
		goto qi_dian;
	}
}

//-----------------------------------------------------------------------------------------------------------

void gang_wei_f_in(gang_wei *head, gang_wei *p)
{
	ifstream in("gang_wei_shu_ju.txt", ios::_Nocreate);

	if (!in.is_open())
		return;

	while (!in.eof())
	{
		gang_wei *a = new gang_wei;

		in >> a->gang_wei_bian_hao >> a->gang_wei_ming_cheng >> a->basic_gong_zi >> a->zhi_ze;

		if (in.fail())
		{
			delete a;

			break;
		}

		if (head->next == NULL)
		{
			a->next = head->next;
			head->next = a;
			p->next = a;
		}
		else
		{
			p->next->next = a;
			a->next = NULL;
			p->next = a;
		}
	}
	in.close();
}

void gang_wei_in(gang_wei *head, gang_wei *p)
{
	gang_wei *a = new gang_wei;

	if (head->next == NULL)
		a->gang_wei_bian_hao = 1;
	else
		a->gang_wei_bian_hao = p->next->gang_wei_bian_hao + 1;

	gang_wei *b = head->next;

	while (b != NULL)
	{
		if (a->gang_wei_bian_hao == b->gang_wei_bian_hao)
		{
			a->gang_wei_bian_hao++;

			b = head->next;
		}
		else
			b = b->next;
	}

	cout << "\n\t\t请输入岗位名称:"; cin >> a->gang_wei_ming_cheng;
	cout << "\n\t\t请输入岗位基本工资(实数):"; cin >> a->basic_gong_zi;
	cout << "\n\t\t请输入岗位职责:"; cin >> a->zhi_ze;

	if (head->next == NULL)
	{
		a->next = head->next;
		head->next = a;
		p->next = a;
	}
	else
	{
		p->next->next = a;
		a->next = NULL;
		p->next = a;
	}

	gang_wei_f_out(head);   // 储存到文件 gang_wei_shu_ju.txt

	cout << "\n\t\t输入完毕!" << endl << "\n\t(任意键返回)"; system("pause");
}

void gang_wei_put(gang_wei *head)
{
	if (head->next == NULL)
	{
		cout << "\n\t\t没有岗位信息!" << endl;

		return;
	}

	gang_wei *b = head->next;

	cout << "\n     岗位编号     " << "岗位名称     " << "岗位基本工资     " << "岗位职责     " << endl;
	cout << "   |-----------------------------------------------------------------------------------------------------|" << endl;

	while (b != NULL)
	{
		cout << setw(9) << b->gang_wei_bian_hao << setw(16) << b->gang_wei_ming_cheng << setw(15) << b->basic_gong_zi << "         " << b->zhi_ze << endl;
		cout << "   |-----------------------------------------------------------------------------------------------------|" << endl;

		b = b->next;
	}
}

void gang_wei_del(gang_wei *head)
{
	if (head->next == NULL)
	{
		cout << "\n\t\t没有可供删除的岗位信息!" << endl;

		cout << "\n\t(任意键返回)";

		system("pause");

		return;
	}

	gang_wei_put(head);

	cout << "\n请输入要删除的岗位的编号:";

	int n;
	cin >> n;

	zhi_gong zhi_gong_head;
	zhi_gong_head.next = NULL;

	zhi_gong zhi_gong_p;
	zhi_gong_p.next = NULL;

	zhi_gong_f_in(&zhi_gong_head, &zhi_gong_p);

	zhi_gong *b2 = zhi_gong_head.next;

	while (b2 != NULL)
	{
		if (b2->gang_wei_bian_hao == n)
		{
			cout << "\n\t\t该岗位有员工,不能删除!" << endl;
			cout << "\n\t(任意键返回)"; system("pause");
			return;
		}

		b2 = b2->next;
	}

	zhi_gong_dong_tai_hui_shou(&zhi_gong_head);

	gang_wei *last = NULL;
	gang_wei *b = head->next;

	int y = 1;

	while (b != NULL)
	{
		if (b->gang_wei_bian_hao == n)
		{
			y = 0;
			if (b->gang_wei_bian_hao == head->next->gang_wei_bian_hao)
			{
				head->next = b->next;
				delete b;
				gang_wei_f_out(head);
				cout << "\n\t\t删除成功!" << endl;
				break;
			}
			else if (b->next == NULL)
			{
				last->next = NULL;
				delete b;
				gang_wei_f_out(head);
				cout << "\n\t\t删除成功!" << endl;
				break;
			}
			else
			{
				last->next = b->next;
				delete b;
				gang_wei_f_out(head);
				cout << "\n\t\t删除成功!" << endl;
				break;
			}
		}
		last = b;
		b = b->next;
	}
	if (y == 1)
		cout << "\n\t\t岗位系统中并未录入此岗位,请确认输入的岗位编号是否有误!" << endl;

	cout << "\n\t(任意键返回)"; system("pause");
}

void gang_wei_f_out(gang_wei *head)
{
	ofstream outf("gang_wei_shu_ju.txt");

	gang_wei *b = head->next;

	while (b != NULL)
	{
		outf << b->gang_wei_bian_hao << " " << b->gang_wei_ming_cheng << " " << b->basic_gong_zi << " " << b->zhi_ze << "\n";

		b = b->next;
	}
	outf.close();
}

void gang_wei_xiu_gai(gang_wei *head)
{
	if (head->next == NULL)
	{
		cout << "\n\t\t没有可供修改的岗位信息!" << endl;

		cout << "\n\t(任意键返回)";

		system("pause");

		return;
	}

	gang_wei_put(head);

	cout << "\n\t\t请输入要修改的岗位的编号:";

	int n;
	cin >> n;

	gang_wei *b = head->next;

	int y = 1;

	while (b != NULL)
	{
		if (b->gang_wei_bian_hao == n)
		{
			y = 0;

			cout << "\n\t     1.岗位名称     2.岗位基本工资     3.岗位职责     4.返回\n";

		re_in:

			cout << "\n\t请选择需要修改的岗位信息:";

			char c[100];
			cin >> c;

			switch (c[0])
			{
			case'1':
				cout << "\n\t\t将该岗位名称修改为:";
				cin >> b->gang_wei_ming_cheng;
				gang_wei_f_out(head);
				cout << "\n\t\t修改成功!";
				break;

			case'2':
				cout << "\n\t\t将该岗位基本工资修改为:";
				cin >> b->basic_gong_zi;
				gang_wei_f_out(head);
				cout << "\n\t\t修改成功!";
				break;

			case'3':
				cout << "\n\t\t将该岗位职责修改为:";
				cin >> b->zhi_ze;
				gang_wei_f_out(head);
				cout << "\n\t\t修改成功!";
				break;

			case'4':
				return;

			default:
				cout << "\n\t\t请确认输入的功能号码是否有误!并重新输入!" << endl;
				goto re_in;
			}
		}
		b = b->next;
	}
	if (y == 1)
		cout << "\n\t\t岗位系统中并未录入此岗位,请确认输入的岗位编号是否有误!" << endl;

	cout << "\n\t(任意键返回)"; system("pause");
}

void gang_wei_dong_tai_hui_shou(gang_wei *head)
{
	if (head->next == NULL)
		return;

	gang_wei *a = head->next;
	gang_wei *temp = NULL;

	while (a != NULL)
	{
		temp = a;

		a = a->next;

		delete temp;
	}
}

//-----------------------------------------------------------------------------------------------------------

void gang_wei_deng_ji_f_in(gang_wei_deng_ji *head, gang_wei_deng_ji *p)
{
	ifstream in("gang_wei_deng_ji_shu_ju.txt", ios::_Nocreate);

	if (!in.is_open())
		return;

	while (!in.eof())
	{
		gang_wei_deng_ji *a = new gang_wei_deng_ji;

		in >> a->gang_wei_deng_ji_bian_hao >> a->gang_wei_deng_ji_ming_cheng >> a->gong_zi_xi_shu;

		if (in.fail())
		{
			delete a;

			break;
		}

		if (head->next == NULL)
		{
			a->next = head->next;
			head->next = a;
			p->next = a;
		}
		else
		{
			p->next->next = a;
			a->next = NULL;
			p->next = a;
		}
	}
	in.close();
}

void gang_wei_deng_ji_in(gang_wei_deng_ji *head, gang_wei_deng_ji *p)
{
	gang_wei_deng_ji *a = new gang_wei_deng_ji;

	if (head->next == NULL)
		a->gang_wei_deng_ji_bian_hao = 1;
	else
		a->gang_wei_deng_ji_bian_hao = p->next->gang_wei_deng_ji_bian_hao + 1;

	gang_wei_deng_ji *b = head->next;

	while (b != NULL)
	{
		if (a->gang_wei_deng_ji_bian_hao == b->gang_wei_deng_ji_bian_hao)
		{
			a->gang_wei_deng_ji_bian_hao++;

			b = head->next;
		}
		else
			b = b->next;
	}

	cout << "\n\t\t请输入岗位等级名称:"; cin >> a->gang_wei_deng_ji_ming_cheng;
	cout << "\n\t\t请输入位等级工资系数:"; cin >> a->gong_zi_xi_shu;

	if (head->next == NULL)
	{
		a->next = head->next;
		head->next = a;
		p->next = a;
	}
	else
	{
		p->next->next = a;
		a->next = NULL;
		p->next = a;
	}

	gang_wei_deng_ji_f_out(head);   // 储存到文件 gang_wei_deng_ji_shu_ju.txt

	cout << "\n\t\t输入完毕!" << endl << "\n\t(任意键返回)"; system("pause");
}

void gang_wei_deng_ji_put(gang_wei_deng_ji *head)
{
	if (head->next == NULL)
	{
		cout << "\n\t\t没有岗位等级信息!" << endl;

		return;
	}

	gang_wei_deng_ji *b = head->next;

	cout << "\n     岗位等级编号     " << "岗位等级名称     " << "岗位等级工资系数     " << endl;
	cout << "   |------------------------------------------------------|" << endl;

	while (b != NULL)
	{
		cout << setw(12) << b->gang_wei_deng_ji_bian_hao << setw(19) << b->gang_wei_deng_ji_ming_cheng << setw(18) << b->gong_zi_xi_shu << endl;
		cout << "   |------------------------------------------------------|" << endl;

		b = b->next;
	}
}

void gang_wei_deng_ji_del(gang_wei_deng_ji *head)
{
	if (head->next == NULL)
	{
		cout << "\n\t\t没有可供删除的岗位等级信息!" << endl;

		cout << "\n\t(任意键返回)";

		system("pause");

		return;
	}

	gang_wei_deng_ji_put(head);

	cout << "\n请输入要删除的岗位等级的编号:";

	int n;
	cin >> n;

	zhi_gong zhi_gong_head;
	zhi_gong_head.next = NULL;

	zhi_gong zhi_gong_p;
	zhi_gong_p.next = NULL;

	zhi_gong_f_in(&zhi_gong_head, &zhi_gong_p);

	zhi_gong *b2 = zhi_gong_head.next;

	while (b2 != NULL)
	{
		if (b2->gang_wei_deng_ji_bian_hao == n)
		{
			cout << "\n\t\t该岗位等级有员工,不能删除!" << endl;
			cout << "\n\t(任意键返回)"; system("pause");
			return;
		}

		b2 = b2->next;
	}

	zhi_gong_dong_tai_hui_shou(&zhi_gong_head);

	gang_wei_deng_ji *last = NULL;
	gang_wei_deng_ji *b = head->next;

	int y = 1;

	while (b != NULL)
	{
		if (b->gang_wei_deng_ji_bian_hao == n)
		{
			y = 0;
			if (b->gang_wei_deng_ji_bian_hao == head->next->gang_wei_deng_ji_bian_hao)
			{
				head->next = b->next;
				delete b;
				gang_wei_deng_ji_f_out(head);
				cout << "\n\t\t删除成功!" << endl;
				break;
			}
			else if (b->next == NULL)
			{
				last->next = NULL;
				delete b;
				gang_wei_deng_ji_f_out(head);
				cout << "\n\t\t删除成功!" << endl;
				break;
			}
			else
			{
				last->next = b->next;
				delete b;
				gang_wei_deng_ji_f_out(head);
				cout << "\n\t\t删除成功!" << endl;
				break;
			}
		}
		last = b;
		b = b->next;
	}
	if (y == 1)
		cout << "\n\t\t岗位等级系统中并未录入此岗位等级,请确认输入的岗位等级编号是否有误!" << endl;

	cout << "\n\t(任意键返回)"; system("pause");
}

void gang_wei_deng_ji_f_out(gang_wei_deng_ji *head)
{
	ofstream outf("gang_wei_deng_ji_shu_ju.txt");

	gang_wei_deng_ji *b = head->next;

	while (b != NULL)
	{
		outf << b->gang_wei_deng_ji_bian_hao << " " << b->gang_wei_deng_ji_ming_cheng << " " << b->gong_zi_xi_shu << "\n";

		b = b->next;
	}
	outf.close();
}

void gang_wei_deng_ji_xiu_gai(gang_wei_deng_ji *head)
{
	if (head->next == NULL)
	{
		cout << "\n\t\t没有可供修改的岗位等级信息!" << endl;

		cout << "\n\t(任意键返回)";

		system("pause");

		return;
	}

	gang_wei_deng_ji_put(head);

	cout << "\n\t\t请输入要修改的岗位等级的编号:";

	int n;
	cin >> n;

	gang_wei_deng_ji *b = head->next;

	int y = 1;

	while (b != NULL)
	{
		if (b->gang_wei_deng_ji_bian_hao == n)
		{
			y = 0;

			cout << "\n\t     1.岗位名称     2.岗位等级工资系数     3.返回\n";

		re_in:

			cout << "\n\t请选择需要修改的岗位等级信息:";

			char c[100];
			cin >> c;

			switch (c[0])
			{
			case'1':
				cout << "\n\t\t将该岗位名称修改为:";
				cin >> b->gang_wei_deng_ji_ming_cheng;
				gang_wei_deng_ji_f_out(head);
				cout << "\n\t\t修改成功!";
				break;

			case'2':
				cout << "\n\t\t将该岗位等级工资系数修改为:";
				cin >> b->gong_zi_xi_shu;
				gang_wei_deng_ji_f_out(head);
				cout << "\n\t\t修改成功!";
				break;

			case'3':
				return;

			default:
				cout << "\n\t\t请确认输入的功能号码是否有误!并重新输入!" << endl;
				goto re_in;
			}
		}
		b = b->next;
	}
	if (y == 1)
		cout << "\n\t\t岗位等级系统中并未录入此岗位等级,请确认输入的岗位等级编号是否有误!" << endl;

	cout << "\n\t(任意键返回)"; system("pause");
}

void gang_wei_deng_ji_dong_tai_hui_shou(gang_wei_deng_ji *head)
{
	if (head->next == NULL)
		return;

	gang_wei_deng_ji *a = head->next;
	gang_wei_deng_ji *temp = NULL;

	while (a != NULL)
	{
		temp = a;

		a = a->next;

		delete temp;
	}
}