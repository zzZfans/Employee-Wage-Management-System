#include"sheng_ming.h"

//-----------------------------------------------------------------------------------------------------------

bool zhi_gong_gong_zi_guan_li()
{
	gong_zi_xin_xi gong_zi_xin_xi_head;
	gong_zi_xin_xi_head.next = NULL;

	gong_zi_xin_xi gong_zi_xin_xi_p;
	gong_zi_xin_xi_p.next = NULL;

	gong_zi_xin_xi_f_in(&gong_zi_xin_xi_head, &gong_zi_xin_xi_p);

qi_dian:

	system("cls");

	cout << "\n";
	cout << "\n\t\t*************************职工工资管理*************************\n";
	cout << "\t\t*                                                            *\n";
	cout << "\t\t*                                                            *\n";
	cout << "\t\t*   1.月份工资基础数据生成   2.职工工资输入   3.职工工资单   *\n";
	cout << "\t\t*                                                            *\n";
	cout << "\t\t*                                                            *\n";
	cout << "\t\t*   4.工资查询               5.统计           6.返回         *\n";
	cout << "\t\t*                                                            *\n";
	cout << "\t\t*                                                            *\n";
	cout << "\t\t*                            7.退出                          *\n";
	cout << "\t\t*                                                            *\n";
	cout << "\t\t*                                                            *\n";
	cout << "\t\t**************************************************************\n";

	cout << "\n\t\t请选择功能数字：";

	char x[100];

	cin >> x;      //接受输入

	switch (x[0])
	{
	case '1':
		yue_fen_gong_zi_ji_chu_shu_ju_sheng_cheng(&gong_zi_xin_xi_head, &gong_zi_xin_xi_p);
		cout << "\n\t(任意键返回)"; system("pause");
		goto qi_dian;

	case '2':
		gong_zi_shu_ru(&gong_zi_xin_xi_head);
		goto qi_dian;

	case '3':
		gong_zi_dan(&gong_zi_xin_xi_head);
		cout << "\n\t(任意键返回)"; system("pause");
		goto qi_dian;

	case '4':
		gong_zi_cha_xun(&gong_zi_xin_xi_head);
		cout << "\n\t(任意键返回)"; system("pause");
		goto qi_dian;


	case '5':
		gong_zi_tong_ji(&gong_zi_xin_xi_head);
		cout << "\n\t(任意键返回)"; system("pause");
		goto qi_dian;

	case '6':
		gong_zi_dong_tai_hui_shou(&gong_zi_xin_xi_head);
		return true;

	case '7':
		gong_zi_dong_tai_hui_shou(&gong_zi_xin_xi_head);
		return false;

	default:
		cout << "\n\t\t非法输入,将返回目录!\n";
		cout << "\n\t(任意键返回)"; system("pause");
		goto qi_dian;
	}
}

//-----------------------------------------------------------------------------------------------------------
void yue_fen_gong_zi_ji_chu_shu_ju_sheng_cheng(gong_zi_xin_xi *head, gong_zi_xin_xi *p)
{
	zhi_gong zhi_gong_head;
	zhi_gong_head.next = NULL;

	zhi_gong zhi_gong_p;
	zhi_gong_p.next = NULL;

	zhi_gong_f_in(&zhi_gong_head, &zhi_gong_p);

	zhi_gong *a = zhi_gong_head.next;
	//-----------------------------------------------------------------------------------------------------------

	gang_wei gang_wei_head;
	gang_wei_head.next = NULL;

	gang_wei gang_wei_p;
	gang_wei_p.next = NULL;

	gang_wei_f_in(&gang_wei_head, &gang_wei_p);

	//-----------------------------------------------------------------------------------------------------------

	gang_wei_deng_ji gang_wei_deng_ji_head;
	gang_wei_deng_ji_head.next = NULL;

	gang_wei_deng_ji gang_wei_deng_ji_p;
	gang_wei_deng_ji_p.next = NULL;

	gang_wei_deng_ji_f_in(&gang_wei_deng_ji_head, &gang_wei_deng_ji_p);

	//-----------------------------------------------------------------------------------------------------------

	if (a == NULL)
	{
		cout << "\n\t\t没有数据可生成!" << endl;
		return;
	}

	while (a != NULL)
	{
		gong_zi_xin_xi *b = new gong_zi_xin_xi;

		b->gong_hao = a->gong_hao;

		gong_zi_xin_xi *e = head->next;

		int y = 1;

		while (e != NULL)
		{
			if (b->gong_hao == e->gong_hao)
			{
				y = 0;
				delete b;
				break;
			}
			e = e->next;
		}

		if (y == 1)
		{
			gang_wei *c = gang_wei_head.next;
			gang_wei_deng_ji *d = gang_wei_deng_ji_head.next;

			double basic, basic_xi_shu;

			while (c != NULL)
			{
				if (a->gang_wei_bian_hao == c->gang_wei_bian_hao)
				{
					basic = c->basic_gong_zi;
					break;
				}
				c = c->next;
			}

			while (d != NULL)
			{
				if (a->gang_wei_deng_ji_bian_hao == d->gang_wei_deng_ji_bian_hao)
				{
					basic_xi_shu = d->gong_zi_xi_shu;
					break;
				}
				d = d->next;
			}

			b->basic_gong_zi = basic * basic_xi_shu;

			time_t now = time(0);
			char tmp[64];
			strftime(tmp, sizeof(tmp), "%Y/%m/%d—%X", localtime(&now));
			strcpy_s(b->time, 64, tmp);

			if (head->next == NULL)
			{
				b->next = head->next;
				head->next = b;
				p->next = b;
			}
			else
			{
				p->next->next = b;
				b->next = NULL;
				p->next = b;
			}

			gong_zi_xin_xi_f_out(head);
		}
		a = a->next;
	}
	cout << "\n\t\t月份工资基础数据生成完毕!" << endl;
}

void gong_zi_xin_xi_f_out(gong_zi_xin_xi *head)
{
	ofstream outf("gong_zi_shu_ju.txt");

	gong_zi_xin_xi *b = head->next;

	while (b != NULL)
	{
		outf << b->gong_hao << " " << b->time << " " << b->basic_gong_zi << " " << b->ji_xiao << " " << b->jia_ban << " "\
			<< b->jiang_li << " " << b->yang_lao << " " << b->zhi_ye_nian_jin << " " << b->gong_ji_jin << " " << b->shi_ye_bao_xian << " "\
			<< b->yi_liao_bao_xian << " " << b->ge_shui << " " << b->ying_fa << " " << b->shi_fa << "\n";

		b = b->next;
	}
	outf.close();
}

void gong_zi_xin_xi_f_in(gong_zi_xin_xi *head, gong_zi_xin_xi *p)
{
	ifstream in("gong_zi_shu_ju.txt", ios::_Nocreate);

	if (!in.is_open())
		return;

	while (!in.eof())
	{
		gong_zi_xin_xi *b = new gong_zi_xin_xi;

		in >> b->gong_hao >> b->time >> b->basic_gong_zi >> b->ji_xiao >> b->jia_ban >> \
			b->jiang_li >> b->yang_lao >> b->zhi_ye_nian_jin >> b->gong_ji_jin >> b->shi_ye_bao_xian >> \
			b->yi_liao_bao_xian >> b->ge_shui >> b->ying_fa >> b->shi_fa;

		if (in.fail())
		{
			delete b;

			break;
		}

		if (head->next == NULL)
		{
			b->next = head->next;
			head->next = b;
			p->next = b;
		}
		else
		{
			p->next->next = b;
			b->next = NULL;
			p->next = b;
		}
	}
	in.close();
}

void gong_zi_dan(gong_zi_xin_xi *head)
{
	if (head->next == NULL)
	{
		cout << "\n\t\t没有工资信息!" << endl;

		return;
	}

	gong_zi_xin_xi *b = head->next;

	cout << "\n     职工工号     " << "     工资时间          " << "基本工资     " << "工作绩效     "\
		<< "加班工资     " << "奖励工资     " << "养老保险     " << "职业年金     " << "公积金     " << "失业保险     " \
		<< "医疗保险     " << "个税     " << "应发数     " << "实发数     " << endl;
	cout << "   |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;

	while (b != NULL)
	{
		cout << setprecision(2) << fixed << setw(9) << b->gong_hao << " " << setw(27) << b->time << " " << setw(11) << b->basic_gong_zi << " " << setw(12) << b->ji_xiao << " " << setw(12) << b->jia_ban << " "\
			<< setw(12) << b->jiang_li << " " << setw(11) << b->yang_lao << " " << setw(12) << b->zhi_ye_nian_jin << " " << setw(12) << b->gong_ji_jin << " " << setw(10) << b->shi_ye_bao_xian << " "\
			<< setw(12) << b->yi_liao_bao_xian << " " << setw(10) << b->ge_shui << " " << setw(10) << b->ying_fa << " " << setw(10) << b->shi_fa << "\n";
		cout << "   |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;

		b = b->next;
	}
}

void gong_zi_shu_ru(gong_zi_xin_xi *head)
{
	if (head->next == NULL)
	{
		cout << "\n\t\t没有基础工资数据!" << endl;

		cout << "\n\t(任意键返回)"; system("pause");

		return;
	}

	gong_zi_dan(head);

ji_xu_shu_ru:

	cout << "\n\t\t请输入将要输入工资的职工工号:";

	int n;
	cin >> n;

	gong_zi_xin_xi *b = head->next;

	int y = 1;

	while (b != NULL)
	{
		if (b->gong_hao == n)
		{
			y = 0;

			cout << "\n\t\t请输入工作绩效:"; cin >> b->ji_xiao;
			cout << "\n\t\t请输入加班工资:"; cin >> b->jia_ban;
			cout << "\n\t\t请输入奖励工资:"; cin >> b->jiang_li;

			double all = b->basic_gong_zi + b->ji_xiao + b->jia_ban + b->jiang_li;

			b->yang_lao = all * 0.08;
			b->zhi_ye_nian_jin = all * 0.04;
			b->gong_ji_jin = all * 0.12;
			b->yi_liao_bao_xian = all * 0.01;

			double ying_na_shui = all - b->yang_lao - b->zhi_ye_nian_jin - b->gong_ji_jin - b->yi_liao_bao_xian - b->shi_ye_bao_xian;

			if (ying_na_shui <= 3000)
				b->ge_shui = ying_na_shui * 0.03;
			else if (3000 < ying_na_shui&&ying_na_shui <= 12000)
				b->ge_shui = ying_na_shui * 0.1 - 210;
			else if (12000 < ying_na_shui&&ying_na_shui <= 25000)
				b->ge_shui = ying_na_shui * 0.2 - 1410;
			else if (25000 < ying_na_shui&&ying_na_shui <= 35000)
				b->ge_shui = ying_na_shui * 0.25 - 2660;
			else if (35000 < ying_na_shui&&ying_na_shui <= 55000)
				b->ge_shui = ying_na_shui * 0.3 - 4410;
			else if (55000 < ying_na_shui&&ying_na_shui <= 80000)
				b->ge_shui = ying_na_shui * 0.35 - 7160;
			else
				b->ge_shui = ying_na_shui * 0.45 - 15160;

			b->ying_fa = all;

			b->shi_fa = ying_na_shui - b->ge_shui;

			time_t now = time(0);
			char tmp[64];
			strftime(tmp, sizeof(tmp), "%Y/%m/%d—%X", localtime(&now));
			strcpy_s(b->time, 64, tmp);

			gong_zi_xin_xi_f_out(head);

			break;
		}
		b = b->next;
	}

	if (y == 1)
		cout << "\n\t\t职工工资数据系统中并未录入此职工,请确认输入的职工工号是否有误!" << endl;

	cout << "\n\t\t\t输入完毕!" << endl;
	cout << "\n\t\t继续输入(Y(y)/N(n))?";
	cout << "\n\n\t\t\t请选择:";
	char x;
	cin >> x;
	while ((x != 'y') && (x != 'n') && (x != 'Y') && (x != 'N'))
	{
		cout << "\n\t\t输入错误!请重新输入(Y(y)/N(n)):";
		cout << "\n\n\t\t\t请选择:";
		cin >> x;
	}

	if (x == 'Y' || x == 'y')
		goto ji_xu_shu_ru;

	cout << "\n\n\t(任意键返回)"; system("pause");
}

void gong_zi_cha_xun(gong_zi_xin_xi *head)
{
	cout << "\n\t\t请输入工号:";

	int x; cin >> x;

	gong_zi_xin_xi *b = head->next;

	while (b != NULL)
	{
		if (b->gong_hao == x)
		{
			cout << "\n     职工工号     " << "     工资时间          " << "基本工资     " << "工作绩效     "\
				<< "加班工资     " << "奖励工资     " << "养老保险     " << "职业年金     " << "公积金     " << "失业保险     " \
				<< "医疗保险     " << "个税     " << "应发数     " << "实发数     " << endl;
			cout << "   |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
			cout << setprecision(2) << fixed << setw(9) << b->gong_hao << " " << setw(27) << b->time << " " << setw(11) << b->basic_gong_zi << " " << setw(12) << b->ji_xiao << " " << setw(12) << b->jia_ban << " "\
				<< setw(12) << b->jiang_li << " " << setw(11) << b->yang_lao << " " << setw(12) << b->zhi_ye_nian_jin << " " << setw(12) << b->gong_ji_jin << " " << setw(10) << b->shi_ye_bao_xian << " "\
				<< setw(12) << b->yi_liao_bao_xian << " " << setw(10) << b->ge_shui << " " << setw(10) << b->ying_fa << " " << setw(10) << b->shi_fa << "\n";
			cout << "   |------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;

			return;
		}
		b = b->next;
	}
	cout << "\n\t\t没有该工号的职工!" << endl;
}

void gong_zi_tong_ji(gong_zi_xin_xi *head)
{
	gong_zi_xin_xi *a = head->next;

	if (a == NULL)
	{
		cout << "\n\t\t没有工资数据!" << endl;

		return;
	}

	double zong_ying_fa = 0;
	double zong_shi_fa = 0;
	double ying_shi_cha = 0;
	double zui_gao_gong_zi = 0;
	double ping_jun_gong_zi = 0;

	int n = 0;

	while (a != NULL)
	{
		zong_ying_fa += a->ying_fa;

		zong_shi_fa += a->shi_fa;

		if (a->ying_fa > zui_gao_gong_zi)
			zui_gao_gong_zi = a->ying_fa;

		n++;

		a = a->next;
	}

	ying_shi_cha = zong_ying_fa - zong_shi_fa;
	ping_jun_gong_zi = zong_ying_fa / n;

	cout << fixed << setprecision(2) << "\n\t\t总应发:" << zong_ying_fa << "\t\t总实发:" << zong_shi_fa << "\t\t应实差:" << ying_shi_cha;
	cout << "\n\n\t\t最高工资:" << zui_gao_gong_zi << "\t\t平均工资:" << ping_jun_gong_zi << "\t\t未完待续···" << endl;
}

void gong_zi_dong_tai_hui_shou(gong_zi_xin_xi *head)
{
	if (head->next == NULL)
		return;

	gong_zi_xin_xi *a = head->next;
	gong_zi_xin_xi *temp = NULL;

	while (a != NULL)
	{
		temp = a;

		a = a->next;

		delete temp;
	}
}