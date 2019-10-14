#include"sheng_ming.h"

//-----------------------------------------------------------------------------------------------------------

bool zhi_gong_ji_ben_xin_xi_guan_li()
{
	zhi_gong zhi_gong_head;
	zhi_gong_head.next = NULL;

	zhi_gong zhi_gong_p;
	zhi_gong_p.next = NULL;

	zhi_gong_f_in(&zhi_gong_head, &zhi_gong_p);

qi_dian:

	system("cls");

	cout << "\n";
	cout << "\n\t\t********************职工基本信息管理********************\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t*   1.增加职工信息   2.修改职工信息   3.删除职工信息   *\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t*   4.浏览职工信息   5.查询           6.返回           *\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t*                    7.退出                            *\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t********************************************************\n";

	cout << "\n\t\t请选择功能数字：";

	char x[100];

	cin >> x;      //接受输入

	switch (x[0])
	{
	case '1':
		zhi_gong_in(&zhi_gong_head, &zhi_gong_p);
		goto qi_dian;

	case '2':
		zhi_gong_xiu_gai(&zhi_gong_head);
		goto qi_dian;

	case '3':
		zhi_gong_del(&zhi_gong_head);
		goto qi_dian;

	case '4':
		zhi_gong_put(&zhi_gong_head);
		cout << "\n\t(任意键返回)"; system("pause");
		goto qi_dian;

	case '5':
		zhi_gong_cha_xun(&zhi_gong_head);
		goto qi_dian;

	case '6':
		zhi_gong_dong_tai_hui_shou(&zhi_gong_head);
		return true;

	case '7':
		zhi_gong_dong_tai_hui_shou(&zhi_gong_head);
		return false;

	default:
		cout << "\n\t\t非法输入,将返回目录!\n";
		cout << "\n\t(任意键返回)"; system("pause");
		goto qi_dian;
	}
}

//-----------------------------------------------------------------------------------------------------------

void zhi_gong_f_in(zhi_gong *head, zhi_gong *p)
{
	ifstream in("zhi_gong_shu_ju.txt", ios::_Nocreate);

	if (!in.is_open())
		return;

	while (!in.eof())
	{
		zhi_gong *a = new zhi_gong;

		in >> a->gong_hao >> a->name >> a->sex >> a->age >> a->chu_sheng_day >> a->ru_zhi_day >> a->bu_men_bian_hao >> a->gang_wei_bian_hao\
			>> a->gang_wei_deng_ji_bian_hao >> a->jia_ting_zhu_zhi >> a->dian_hua >> a->dian_zi_you_jian;

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

void zhi_gong_in(zhi_gong *head, zhi_gong *p)
{
	bu_men bu_men_head;
	bu_men_head.next = NULL;

	bu_men bu_men_p;
	bu_men_p.next = NULL;

	bu_men_f_in(&bu_men_head, &bu_men_p);

	if (bu_men_head.next == NULL)
	{
		cout << "\n\t\t无部门数据,无法增加职工信息!" << endl;
		cout << "\n\t(任意键返回)"; system("pause");
		return;
	}

	gang_wei gang_wei_head;
	gang_wei_head.next = NULL;

	gang_wei gang_wei_p;
	gang_wei_p.next = NULL;

	gang_wei_f_in(&gang_wei_head, &gang_wei_p);

	if (gang_wei_head.next == NULL)
	{
		cout << "\n\t\t无岗位数据,无法增加职工信息!" << endl;
		cout << "\n\t(任意键返回)"; system("pause");
		return;
	}

	gang_wei_deng_ji gang_wei_deng_ji_head;
	gang_wei_deng_ji_head.next = NULL;

	gang_wei_deng_ji gang_wei_deng_ji_p;
	gang_wei_deng_ji_p.next = NULL;

	gang_wei_deng_ji_f_in(&gang_wei_deng_ji_head, &gang_wei_deng_ji_p);

	if (gang_wei_deng_ji_head.next == NULL)
	{
		cout << "\n\t\t无岗位等级数据,无法增加职工信息!" << endl;
		cout << "\n\t(任意键返回)"; system("pause");
		return;
	}

	zhi_gong *a = new zhi_gong;

	if (head->next == NULL)
		a->gong_hao = 1;
	else
		a->gong_hao = p->next->gong_hao + 1;

	zhi_gong *b = head->next;

	while (b != NULL)
	{
		if (a->gong_hao == b->gong_hao)
		{
			a->gong_hao++;

			b = head->next;
		}
		else
			b = b->next;
	}

	cout << "\n\t\t请输入职工名称:"; cin >> a->name;

	cout << "\n\t\t请输入职工性别:"; cin >> a->sex;
	while ((strcmp(a->sex, "男") != 0) && (strcmp(a->sex, "女") != 0))
	{
		cout << "\n\t\t输入错误!请重新输入(男或者女):";

		cin >> a->sex;
	}

	cout << "\n\t\t请输入职工出生日期(格式为2000-01-22):"; cin >> a->chu_sheng_day;
	while (a->chu_sheng_day[4] != '-' || a->chu_sheng_day[7] != '-')
	{
		cout << "\n\t\t格式错误,请重新输入:";

		cin >> a->chu_sheng_day;
	}
	char x[5] = { 0 };
	int i = 0;
	for (; i < 4; i++)
		x[i] = a->chu_sheng_day[i];
	x[i] = '\0';

	cout << "\n\t\t请输入职工入职日期(格式为2000-01-22):"; cin >> a->ru_zhi_day;
	while (a->ru_zhi_day[4] != '-' || a->ru_zhi_day[7] != '-')
	{
		cout << "\n\t\t格式错误,请重新输入:";

		cin >> a->ru_zhi_day;
	}
	char y[5] = { 0 };
	int q = 0;
	for (; q < 4; q++)
		y[q] = a->ru_zhi_day[q];
	y[q] = '\0';

	a->age = atoi(y) - atoi(x);
	//-----------------------------------------------------------------------------------------------------------
re_in_bu_men:

	cout << "\n\t\t请输入职工所属部门编号:"; cin >> a->bu_men_bian_hao;

	bu_men *b2 = bu_men_head.next;

	while (1)
	{
		if (b2 == NULL)
		{
			cout << "\n\t\t系统中并未录入此部门,请确认输入的部门编号是否有误!并重新输入!" << endl;

			goto re_in_bu_men;
		}

		if (b2->bu_men_bian_hao == a->bu_men_bian_hao)
			break;

		b2 = b2->next;
	}

	bu_men_dong_tai_hui_shou(&bu_men_head);
	//-----------------------------------------------------------------------------------------------------------
re_in_gang_wei:

	cout << "\n\t\t请输入职工所在岗位编号:"; cin >> a->gang_wei_bian_hao;

	gang_wei *b3 = gang_wei_head.next;

	while (1)
	{
		if (b3 == NULL)
		{
			cout << "\n\t\t系统中并未录入此岗位,请确认输入的岗位编号是否有误!并重新输入!" << endl;

			goto re_in_gang_wei;
		}

		if (b3->gang_wei_bian_hao == a->gang_wei_bian_hao)
			break;

		b3 = b3->next;
	}

	gang_wei_dong_tai_hui_shou(&gang_wei_head);
	//-----------------------------------------------------------------------------------------------------------
re_in_gang_wei_deng_ji:

	cout << "\n\t\t请输入职工所在岗位等级编号:"; cin >> a->gang_wei_deng_ji_bian_hao;

	gang_wei_deng_ji *b4 = gang_wei_deng_ji_head.next;

	while (1)
	{
		if (b4 == NULL)
		{
			cout << "\n\t\t系统中并未录入此岗位等级,请确认输入的岗位等级编号是否有误!并重新输入!" << endl;

			goto re_in_gang_wei_deng_ji;
		}

		if (b4->gang_wei_deng_ji_bian_hao == a->gang_wei_deng_ji_bian_hao)
			break;

		b4 = b4->next;
	}

	gang_wei_deng_ji_dong_tai_hui_shou(&gang_wei_deng_ji_head);
	//-----------------------------------------------------------------------------------------------------------
	cout << "\n\t\t请输入职工家庭住址:"; cin >> a->jia_ting_zhu_zhi;
	cout << "\n\t\t请输入职工电话号码:"; cin >> a->dian_hua;
	cout << "\n\t\t请输入职工电子邮件:"; cin >> a->dian_zi_you_jian;


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

	zhi_gong_f_out(head);   // 储存到文件 zhi_gong_shu_ju.txt

	cout << "\n\t\t输入完毕!" << endl << "\n\t(任意键返回)"; system("pause");
}

void zhi_gong_put(zhi_gong *head)
{
	if (head->next == NULL)
	{
		cout << "\n\t\t没有职工信息!" << endl;

		return;
	}

	zhi_gong *b = head->next;

	cout << "\n     职工工号     " << "职工姓名     " << "性别     " << "年龄     " << "出生日期     " \
		<< "到本单位日期     " << "所属部门编号     " << "所属岗位编号     " << "岗位等级编号     "\
		<< "家庭住址     " << "联系电话     " << "电子邮件     " << endl;
	cout << "   |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;

	while (b != NULL)
	{
		cout << setw(9) << b->gong_hao << setw(16) << b->name << setw(9) << b->sex << setw(9) \
			<< b->age << setw(15) << b->chu_sheng_day << setw(15) << b->ru_zhi_day << setw(12) \
			<< b->bu_men_bian_hao << setw(17) << b->gang_wei_bian_hao\
			<< setw(17) << b->gang_wei_deng_ji_bian_hao << setw(22) << b->jia_ting_zhu_zhi << setw(12)\
			<< b->dian_hua << setw(22) << b->dian_zi_you_jian << endl;
		cout << "   |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;

		b = b->next;
	}
}

void zhi_gong_del(zhi_gong *head)
{
	if (head->next == NULL)
	{
		cout << "\n\t\t没有可供删除的职工信息!" << endl;

		cout << "\n\t(任意键返回)";

		system("pause");

		return;
	}

	zhi_gong_put(head);

	cout << "\n\t请输入要删除的职工的工号:";

	int n;
	cin >> n;

	zhi_gong *last = NULL;
	zhi_gong *b = head->next;

	int y = 1;

	while (b != NULL)
	{
		if (b->gong_hao == n)
		{
			y = 0;
			if (b->gong_hao == head->next->gong_hao)
			{
				head->next = b->next;
				delete b;
				zhi_gong_f_out(head);
				cout << "\n\t\t删除成功!" << endl;
				break;
			}
			else if (b->next == NULL)
			{
				last->next = NULL;
				delete b;
				zhi_gong_f_out(head);
				cout << "\n\t\t删除成功!" << endl;
				break;
			}
			else
			{
				last->next = b->next;
				delete b;
				zhi_gong_f_out(head);
				cout << "\n\t\t删除成功!" << endl;
				break;
			}
		}
		last = b;
		b = b->next;
	}
	if (y == 1)
		cout << "\n\t\t职工系统中并未录入此职工,请确认输入的职工工号是否有误!" << endl;

	cout << "\n\t(任意键返回)"; system("pause");
}

void zhi_gong_f_out(zhi_gong *head)
{
	ofstream outf("zhi_gong_shu_ju.txt");

	zhi_gong *b = head->next;

	while (b != NULL)
	{
		outf << b->gong_hao << " " << b->name << " " << b->sex << " " << b->age << " " << b->chu_sheng_day << " "\
			<< b->ru_zhi_day << " " << b->bu_men_bian_hao << " " << b->gang_wei_bian_hao\
			<< " " << b->gang_wei_deng_ji_bian_hao << " " << b->jia_ting_zhu_zhi << " "\
			<< b->dian_hua << " " << b->dian_zi_you_jian << endl;

		b = b->next;
	}
	outf.close();
}

void zhi_gong_xiu_gai(zhi_gong *head)
{
	if (head->next == NULL)
	{
		cout << "\n\t\t没有可供修改的职工信息!" << endl;

		cout << "\n\t(任意键返回)";

		system("pause");

		return;
	}

	zhi_gong_put(head);

	cout << "\n\t\t请输入要修改的职工的编号:";

	int n;
	cin >> n;

	zhi_gong *b = head->next;

	int y = 1;

	while (b != NULL)
	{
		if (b->gong_hao == n)
		{
			y = 0;
			system("cls");
			cout << "\n";
			cout << "\n\t\t********************修改职工基本信息********************\n";
			cout << "\t\t*                                                      *\n";
			cout << "\t\t*                                                      *\n";
			cout << "\t\t*    1.职工姓名     2.职工性别     3.职工出生日期      *\n";
			cout << "\t\t*                                                      *\n";
			cout << "\t\t*                                                      *\n";
			cout << "\t\t*    4.职工上岗日期 5.所属部门     6.所属岗位          *\n";
			cout << "\t\t*                                                      *\n";
			cout << "\t\t*                                                      *\n";
			cout << "\t\t*    7.所属岗位等级 8.家庭住址     9.联系电话          *\n";
			cout << "\t\t*                                                      *\n";
			cout << "\t\t*                                                      *\n";
			cout << "\t\t*    0.电子邮件     a.职工年龄     r.返回              *\n";
			cout << "\t\t*                                                      *\n";
			cout << "\t\t*                                                      *\n";
			cout << "\t\t********************************************************\n";

		re_in:

			cout << "\n\t请选择需要修改的职工信息:";

			char c[100];
			cin >> c;

			switch (c[0])
			{

			case'1':
			{
				cout << "\n\t\t将该职工名称修改为:";
				cin >> b->name;
				zhi_gong_f_out(head);
				cout << "\n\t\t修改成功!";
				break;
			}

			case'2':
			{
				cout << "\n\t\t将该职工性别修改为:";
				cin >> b->sex;
				zhi_gong_f_out(head);
				cout << "\n\t\t修改成功!";
				break;
			}

			case'3':
			{
				cout << "\n\t\t将该职工出生日期修改为:";
				cin >> b->chu_sheng_day;
				while (b->chu_sheng_day[4] != '-' && b->chu_sheng_day[7] != '-')
				{
					cout << "\n\t\t格式错误,请重新输入:";

					cin >> b->chu_sheng_day;
				}
				zhi_gong_f_out(head);
				cout << "\n\t\t修改成功!";
				break;
			}

			case'4':
			{
				cout << "\n\t\t将该职工上岗日期修改为:";
				cin >> b->ru_zhi_day;
				while (b->ru_zhi_day[4] != '-' && b->ru_zhi_day[7] != '-')
				{
					cout << "\n\t\t格式错误,请重新输入:";

					cin >> b->ru_zhi_day;
				}
				zhi_gong_f_out(head);
				cout << "\n\t\t修改成功!";
				break;
			}

			case'5':
			{
			re_in_bu_men:

				cout << "\n\t\t将该职工所属部门修改为:";

				cin >> b->bu_men_bian_hao;

				bu_men bu_men_head;
				bu_men_head.next = NULL;

				bu_men bu_men_p;
				bu_men_p.next = NULL;

				bu_men_f_in(&bu_men_head, &bu_men_p);

				bu_men *b2 = bu_men_head.next;

				while (1)
				{
					if (b2 == NULL)
					{
						cout << "\n\t\t系统中并未录入此部门,请确认输入的部门编号是否有误!并重新输入!" << endl;

						goto re_in_bu_men;
					}

					if (b2->bu_men_bian_hao == b->bu_men_bian_hao)
						break;

					b2 = b2->next;
				}

				bu_men_dong_tai_hui_shou(&bu_men_head);
				zhi_gong_f_out(head);
				cout << "\n\t\t修改成功!";
				break;
			}

			case'6':
			{
			re_in_gang_wei:

				cout << "\n\t\t将该职工所属岗位修改为:";

				cin >> b->gang_wei_bian_hao;

				gang_wei gang_wei_head;
				gang_wei_head.next = NULL;

				gang_wei gang_wei_p;
				gang_wei_p.next = NULL;

				gang_wei_f_in(&gang_wei_head, &gang_wei_p);

				gang_wei *b3 = gang_wei_head.next;

				while (1)
				{
					if (b3 == NULL)
					{
						cout << "\n\t\t系统中并未录入此岗位,请确认输入的岗位编号是否有误!并重新输入!" << endl;

						goto re_in_gang_wei;
					}

					if (b3->gang_wei_bian_hao == b->gang_wei_bian_hao)
						break;

					b3 = b3->next;
				}

				gang_wei_dong_tai_hui_shou(&gang_wei_head);
				zhi_gong_f_out(head);
				cout << "\n\t\t修改成功!";
				break;
			}

			case'7':
			{
			re_in_gang_wei_deng_ji:

				cout << "\n\t\t将该职工所属岗位等级修改为:";

				cin >> b->gang_wei_deng_ji_bian_hao;

				gang_wei_deng_ji gang_wei_deng_ji_head;
				gang_wei_deng_ji_head.next = NULL;

				gang_wei_deng_ji gang_wei_deng_ji_p;
				gang_wei_deng_ji_p.next = NULL;

				gang_wei_deng_ji_f_in(&gang_wei_deng_ji_head, &gang_wei_deng_ji_p);

				gang_wei_deng_ji *b4 = gang_wei_deng_ji_head.next;

				while (1)
				{
					if (b4 == NULL)
					{
						cout << "\n\t\t系统中并未录入此岗位等级,请确认输入的岗位等级编号是否有误!并重新输入!" << endl;

						goto re_in_gang_wei_deng_ji;
					}

					if (b4->gang_wei_deng_ji_bian_hao == b->gang_wei_deng_ji_bian_hao)
						break;

					b4 = b4->next;
				}

				gang_wei_deng_ji_dong_tai_hui_shou(&gang_wei_deng_ji_head);
				zhi_gong_f_out(head);
				cout << "\n\t\t修改成功!";
				break;
			}

			case'8':
			{
				cout << "\n\t\t将该职工家庭住址修改为:";
				cin >> b->jia_ting_zhu_zhi;
				zhi_gong_f_out(head);
				cout << "\n\t\t修改成功!";
				break;
			}

			case'9':
			{
				cout << "\n\t\t将该职工联系电话修改为:";
				cin >> b->dian_hua;
				zhi_gong_f_out(head);
				cout << "\n\t\t修改成功!";
				break;
			}

			case'0':
			{
				cout << "\n\t\t将该职工电子邮件修改为:";
				cin >> b->dian_zi_you_jian;
				zhi_gong_f_out(head);
				cout << "\n\t\t修改成功!";
				break;
			}

			case'a':
			{
				cout << "\n\t\t将该职工年龄修改为:";
				cin >> b->age;
				zhi_gong_f_out(head);
				cout << "\n\t\t修改成功!";
				break;
			}

			case'r':
			{
				return;
			}

			default:
			{
				cout << "\n\t\t请确认输入的功能号码是否有误!并重新输入!" << endl;
				goto re_in;
			}

			}
		}
		b = b->next;
	}
	if (y == 1)
		cout << "\n\t\t职工基本信息系统中并未录入此职工,请确认输入的职工工号是否有误!" << endl;

	cout << "\n\n\t(任意键返回)"; system("pause");
}

void zhi_gong_dong_tai_hui_shou(zhi_gong *head)
{
	if (head->next == NULL)
		return;

	zhi_gong *a = head->next;
	zhi_gong *temp = NULL;

	while (a != NULL)
	{
		temp = a;

		a = a->next;

		delete temp;
	}
}

void zhi_gong_cha_xun(zhi_gong *head)
{
cai_dan:

	system("cls");
	cout << "\n";
	cout << "\n\t\t********************查询职工基本信息********************\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t*    1.按性别           2.按部门编号    3.按岗位编号   *\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t*    4.按岗位等级编号   5.按年龄        6.按名字       *\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t*    7.按工号           8.返回                         *\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t*                                                      *\n";
	cout << "\t\t********************************************************\n";

re_in:

	cout << "\n\t请选择查询依据:";

	char c[100];
	cin >> c;

	switch (c[0])
	{

	case'1':
	{
		int y = 0;

		cout << "\n\t\t请输入性别(男\\女):";

		char sex[10]; cin >> sex;
		while ((strcmp(sex, "男") != 0) && (strcmp(sex, "女") != 0))
		{
			cout << "\n\t\t输入错误!请重新输入性别(男\\女):";

			cin >> sex;
		}

		zhi_gong *b = head->next;

		while (b != NULL)
		{
			if (strcmp(b->sex, sex) == 0)
			{
				y++;

				if (y == 1)
				{
					cout << "\n     职工工号     " << "职工姓名     " << "性别     " << "年龄     " << "出生日期     " \
						<< "到本单位日期     " << "所属部门编号     " << "所属岗位编号     " << "岗位等级编号     "\
						<< "家庭住址     " << "联系电话     " << "电子邮件     " << endl;
					cout << "   |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
				}
				cout << setw(9) << b->gong_hao << setw(16) << b->name << setw(9) << b->sex << setw(9) << b->age \
					<< setw(15) << b->chu_sheng_day << setw(15) << b->ru_zhi_day << setw(12) << b->bu_men_bian_hao\
					<< setw(17) << b->gang_wei_bian_hao\
					<< setw(17) << b->gang_wei_deng_ji_bian_hao << setw(22) << b->jia_ting_zhu_zhi << setw(12)\
					<< b->dian_hua << setw(22) << b->dian_zi_you_jian << endl;
				cout << "   |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
			}
			b = b->next;
		}
		if (y == 0)
			cout << "\n\t\t没有该性别职工信息!";
		else
			cout << "\n\t\t共有" << y << "位该性别职工!";

		cout << "\n\n\t(任意键返回)"; system("pause");

		goto cai_dan;
	}

	case'2':
	{
		int y = 0;

		cout << "\n\t\t请输入部门编号:";

		int x; cin >> x;

		zhi_gong *b = head->next;

		while (b != NULL)
		{
			if (b->bu_men_bian_hao == x)
			{
				y++;

				if (y == 1)
				{
					cout << "\n     职工工号     " << "职工姓名     " << "性别     " << "年龄     " << "出生日期     " \
						<< "到本单位日期     " << "所属部门编号     " << "所属岗位编号     " << "岗位等级编号     "\
						<< "家庭住址     " << "联系电话     " << "电子邮件     " << endl;
					cout << "   |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
				}
				cout << setw(9) << b->gong_hao << setw(16) << b->name << setw(9) << b->sex << setw(9) << b->age << setw(15)\
					<< b->chu_sheng_day << setw(15) << b->ru_zhi_day << setw(12) << b->bu_men_bian_hao\
					<< setw(17) << b->gang_wei_bian_hao\
					<< setw(17) << b->gang_wei_deng_ji_bian_hao << setw(22) << b->jia_ting_zhu_zhi \
					<< setw(12) << b->dian_hua << setw(22) << b->dian_zi_you_jian << endl;
				cout << "   |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
			}
			b = b->next;
		}
		if (y == 0)
			cout << "\n\t\t没有属于该部门的职工!";
		else
			cout << "\n\t\t共有" << y << "位属于该部门的职工!";

		cout << "\n\n\t(任意键返回)"; system("pause");

		goto cai_dan;
	}

	case'3':
	{
		int y = 0;

		cout << "\n\t\t请输入岗位编号:";

		int x; cin >> x;

		zhi_gong *b = head->next;

		while (b != NULL)
		{
			if (b->gang_wei_bian_hao == x)
			{
				y++;

				if (y == 1)
				{
					cout << "\n     职工工号     " << "职工姓名     " << "性别     " << "年龄     " << "出生日期     " \
						<< "到本单位日期     " << "所属部门编号     " << "所属岗位编号     " << "岗位等级编号     "\
						<< "家庭住址     " << "联系电话     " << "电子邮件     " << endl;
					cout << "   |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
				}
				cout << setw(9) << b->gong_hao << setw(16) << b->name << setw(9) << b->sex << setw(9) << b->age << setw(15) << b->chu_sheng_day << setw(15) << b->ru_zhi_day << setw(12) << b->bu_men_bian_hao << setw(17) << b->gang_wei_bian_hao\
					<< setw(17) << b->gang_wei_deng_ji_bian_hao << setw(22) << b->jia_ting_zhu_zhi << setw(12) << b->dian_hua << setw(22) << b->dian_zi_you_jian << endl;
				cout << "   |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
			}
			b = b->next;
		}
		if (y == 0)
			cout << "\n\t\t没有属于该岗位的职工!";
		else
			cout << "\n\t\t共有" << y << "位属于该岗位的职工!";

		cout << "\n\n\t(任意键返回)"; system("pause");

		goto cai_dan;
	}

	case'4':
	{
		int y = 0;

		cout << "\n\t\t请输入岗位等级编号:";

		int x; cin >> x;

		zhi_gong *b = head->next;

		while (b != NULL)
		{
			if (b->gang_wei_deng_ji_bian_hao == x)
			{
				y++;

				if (y == 1)
				{
					cout << "\n     职工工号     " << "职工姓名     " << "性别     " << "年龄     " << "出生日期     " \
						<< "到本单位日期     " << "所属部门编号     " << "所属岗位编号     " << "岗位等级编号     "\
						<< "家庭住址     " << "联系电话     " << "电子邮件     " << endl;
					cout << "   |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
				}
				cout << setw(9) << b->gong_hao << setw(16) << b->name << setw(9) << b->sex << setw(9) << b->age << setw(15) << b->chu_sheng_day << setw(15) << b->ru_zhi_day << setw(12) << b->bu_men_bian_hao << setw(17) << b->gang_wei_bian_hao\
					<< setw(17) << b->gang_wei_deng_ji_bian_hao << setw(22) << b->jia_ting_zhu_zhi << setw(12) << b->dian_hua << setw(22) << b->dian_zi_you_jian << endl;
				cout << "   |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
			}
			b = b->next;
		}
		if (y == 0)
			cout << "\n\t\t没有属于该岗位等级的职工!";
		else
			cout << "\n\t\t共有" << y << "位属于该岗位等级的职工!";

		cout << "\n\n\t(任意键返回)"; system("pause");

		goto cai_dan;
	}

	case'5':
	{
		int y = 0;

		cout << "\n\t\t请输入年龄:";

		int x; cin >> x;

		zhi_gong *b = head->next;

		while (b != NULL)
		{
			if (b->age == x)
			{
				y++;

				if (y == 1)
				{
					cout << "\n     职工工号     " << "职工姓名     " << "性别     " << "年龄     " << "出生日期     " \
						<< "到本单位日期     " << "所属部门编号     " << "所属岗位编号     " << "岗位等级编号     "\
						<< "家庭住址     " << "联系电话     " << "电子邮件     " << endl;
					cout << "   |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
				}
				cout << setw(9) << b->gong_hao << setw(16) << b->name << setw(9) << b->sex << setw(9) << b->age << setw(15) << b->chu_sheng_day << setw(15) << b->ru_zhi_day << setw(12) << b->bu_men_bian_hao << setw(17) << b->gang_wei_bian_hao\
					<< setw(17) << b->gang_wei_deng_ji_bian_hao << setw(22) << b->jia_ting_zhu_zhi << setw(12) << b->dian_hua << setw(22) << b->dian_zi_you_jian << endl;
				cout << "   |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
			}
			b = b->next;
		}
		if (y == 0)
			cout << "\n\t\t没有该年龄的职工!";
		else
			cout << "\n\t\t共有" << y << "位该年龄的职工!";

		cout << "\n\n\t(任意键返回)"; system("pause");

		goto cai_dan;
	}

	case'6':
	{
		cout << "\n\t\t请输入姓名:";

		char name[20]; cin >> name;

		zhi_gong *b = head->next;

		while (b != NULL)
		{
			if (strcmp(b->name, name) == 0)
			{
				cout << "\n     职工工号     " << "职工姓名     " << "性别     " << "年龄     " << "出生日期     " \
					<< "到本单位日期     " << "所属部门编号     " << "所属岗位编号     " << "岗位等级编号     "\
					<< "家庭住址     " << "联系电话     " << "电子邮件     " << endl;
				cout << "   |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
				cout << setw(9) << b->gong_hao << setw(16) << b->name << setw(9) << b->sex << setw(9) << b->age << setw(15) << b->chu_sheng_day << setw(15) << b->ru_zhi_day << setw(12) << b->bu_men_bian_hao << setw(17) << b->gang_wei_bian_hao\
					<< setw(17) << b->gang_wei_deng_ji_bian_hao << setw(22) << b->jia_ting_zhu_zhi << setw(12) << b->dian_hua << setw(22) << b->dian_zi_you_jian << endl;
				cout << "   |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;

				cout << "\n\n\t(任意键返回)"; system("pause");

				goto cai_dan;
			}
			b = b->next;
		}
		cout << "\n\t\t没有该姓名的职工!";

		cout << "\n\n\t(任意键返回)"; system("pause");

		goto cai_dan;
	}

	case'7':
	{
		cout << "\n\t\t请输入工号:";

		int x; cin >> x;

		zhi_gong *b = head->next;

		while (b != NULL)
		{
			if (b->gong_hao == x)
			{
				cout << "\n     职工工号     " << "职工姓名     " << "性别     " << "年龄     " << "出生日期     " \
					<< "到本单位日期     " << "所属部门编号     " << "所属岗位编号     " << "岗位等级编号     "\
					<< "家庭住址     " << "联系电话     " << "电子邮件     " << endl;
				cout << "   |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
				cout << setw(9) << b->gong_hao << setw(16) << b->name << setw(9) << b->sex << setw(9) << b->age << setw(15) << b->chu_sheng_day << setw(15) << b->ru_zhi_day << setw(12) << b->bu_men_bian_hao << setw(17) << b->gang_wei_bian_hao\
					<< setw(17) << b->gang_wei_deng_ji_bian_hao << setw(22) << b->jia_ting_zhu_zhi << setw(12) << b->dian_hua << setw(22) << b->dian_zi_you_jian << endl;
				cout << "   |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|";

				cout << "\n\n\t(任意键返回)"; system("pause");

				goto cai_dan;
			}
			b = b->next;
		}
		cout << "\n\t\t没有该工号的职工!";

		cout << "\n\n\t(任意键返回)"; system("pause");

		goto cai_dan;
	}

	case'8':
	{
		return;
	}

	default:
	{
		cout << "\n\t\t请确认输入的功能号码是否有误!并重新输入!" << endl;

		goto re_in;
	}

	}
}