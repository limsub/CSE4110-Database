#include <stdio.h>
#include "mysql.h"
#include <stdlib.h>
#include <conio.h>
#include <string>

#include <sstream>
#include <fstream>

#include <iostream>

using namespace std;


#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "libmysql.lib")

const char* host = "localhost";
const char* user = "root";
const char* pw = "dlatmdtjq9076!@";	// 패스워드
const char* db = "new_schema100";	// 디비 이름


char menu() {
	printf("------- SELECT QUERY TYPES -------\n\n");
	printf("\t1. TYPE 1\n");
	printf("\t2. TYPE 2\n");
	printf("\t3. TYPE 3\n");
	printf("\t4. TYPE 4\n");
	printf("\t5. TYPE 5\n");
	printf("\t0. QUIT\n");
	return _getch();
}

int main(void) {

	MYSQL* connection = NULL;
	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;


	const char* query;

	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");

	connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);
	if (connection == NULL)
	{
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}




	else
	{
		printf("Connection Succeed\n");

		if (mysql_select_db(&conn, db))
		{
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}	
		// 여기까지 건들 필요 없다

		
		ifstream pFile("make_table.txt");
		ifstream qFile("insert_value.txt");


		if (pFile.is_open())
		{
			string line;
			while (getline(pFile, line))
			{
				query = line.c_str();
				mysql_query(connection, query);
			}
			pFile.close();
		}
		else
		{
			printf("file open error");
			return 1;
		}

		if (qFile.is_open())
		{
			string line;
			while (getline(qFile, line))
			{
				query = line.c_str();
				mysql_query(connection, query);

			}
			qFile.close();
		}
		else
		{
			printf("file open error");
			return 1;
		}



		
		int state;

		while (1) {
			char type_num = menu();
			char type1_num;
			char type11_num;
			char type12_num;
			char type13_num;

			string type2_year;
			string type2_sub;

			string type3_year;
			string type3_sub;

			string type5_year;
			string type5_month;
			string type5_sub;
			

			system("cls");
			switch (type_num) {
			case '1':
				printf("------- Subtypes in TYPE 1 -------\n");
				printf("\t1. TYPE 1-1\n");
				printf("\t2. TYPE 1-2\n");
				printf("\t3. TYPE 1-3\n");

				type1_num = _getch();
				system("cls");

				switch (type1_num) {
				case '1':
					printf("---- TYPE 1-1 ----\n");
					printf("truck 1721 is destroyed in a crash\n");
					printf("All customers who had a package on the truck at the time of the crash\n");


					query = "select package.shipper_ID, shipper.name		from package, deliver, shipper		where package.shipper_ID = shipper.shipper_ID and deliver.vehicle_ID = '1721' and deliver.vehicle_type = 'truck'	and deliver.package_ID = package.package_ID;";
					state = 0;

					printf("\n");
					printf("customer_ID  customer_name\n");
					printf("-----------  --------------------\n");
					state = mysql_query(connection, query);
					if (state == 0)
					{
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							printf("%11s  %20s\n", sql_row[0], sql_row[1]);
						}
						mysql_free_result(sql_result);
					}

					

					type11_num = _getch();
					system("cls");
					break;
					
				case '2':
					printf("---- TYPE 1-2 ----\n");
					printf("truck 1721 is destroyed in a crash\n");
					printf("All recipients who had a package on the truck at the time of the crash\n");


					query = "select package.customer_ID, customer.name 		from package, deliver, customer		where package.customer_ID = customer.customer_ID and deliver.vehicle_ID = '1721' and deliver.vehicle_type = 'truck' and deliver.package_ID = package.package_ID; ";
					state = 0;

					printf("\n");
					printf("recipient_ID  recipient_name\n");
					printf("------------  --------------------\n");
					state = mysql_query(connection, query);
					if (state == 0)
					{
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							printf("%12s  %20s\n", sql_row[0], sql_row[1]);
						}
						mysql_free_result(sql_result);
					}

					

					type12_num = _getch();
					system("cls");
					break;


				case '3':
					printf("---- TYPE 1-3 ----\n");
					printf("truck 1721 is destroyed in a crash\n");
					printf("The last successful delivery by that truck prior to the crash\n");

					query = "select warehouse.warehouse_address, warehouse.warehouse_name		from start_point, warehouse		where start_point.vehicle_ID = '1721' and start_point.vehicle_type = 'truck' and	start_point.warehouse_address = warehouse.warehouse_address; ";
					state = 0;

					printf("\n");
					printf("warehouse_address  warehouse_name\n");
					printf("-----------------  --------------\n");
					state = mysql_query(connection, query);
					if (state == 0)
					{
						sql_result = mysql_store_result(connection);
						while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
						{
							printf("%17s  %14s\n", sql_row[0], sql_row[1]);
						}
						mysql_free_result(sql_result);
					}


					type13_num = _getch();
					system("cls");
					break;


				case '0':
					break;
				}
				break;

			case '2':
				printf("---- TYPE 2 ----\n");
				printf("the customer who has shipped the most packages in the past year.\n");
				

				printf("Which Year? : ");
				getline(cin, type2_year);


				type2_sub =  "with cnt_list(ID, value) as(select shipper_ID, count(*) as cnt from package where year(package.start_day) = ' " + type2_year + "' group by shipper_ID), max_cnt(value) as(select max(value) from cnt_list) select distinct shipper_ID, max_cnt.value as count		 from package, max_cnt, cnt_list		where cnt_list.value = max_cnt.value and ID = shipper_ID; ";

				printf("\n");
				printf("customer_ID  how many packages?\n");
				printf("-----------  -----------------\n");

				query = type2_sub.c_str();
				state = 0;


				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%11s  %17s\n", sql_row[0], sql_row[1]);
					}
					mysql_free_result(sql_result);
				}


				type13_num = _getch();
				system("cls");
				break;

			case '3':
				printf("---- TYPE 3 ----\n");
				printf("the customer who has spent the most money on shipping in the past year.\n");
				
				printf("Which Year? : ");
				getline(cin, type3_year);


				type3_sub = "with 2022_sum_price(ID, sum) as(select shipper_ID, sum(bill.price) as sum from package, bill where package.bill_ID = bill.bill_ID and year(package.start_day) = '" + type3_year + "' group by shipper_ID ), 2022_top_price(value) as  (select max(sum) from 2022_sum_price ) select ID, sum from 2022_sum_price, 2022_top_price where sum = value; ";

				printf("\n");
				printf("customer_ID  how much money?\n");
				printf("-----------  ---------------\n");

				query = type3_sub.c_str();
				state = 0;


				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%11s  %15s\n", sql_row[0], sql_row[1]);
					}
					mysql_free_result(sql_result);
				}


				type13_num = _getch();
				system("cls");
				break;


			case '4':
				printf("---- TYPE 4 ----\n");
				printf("the packages that were not delivered within the promised time.\n");
				query = "select package_ID, company_name, start_day, end_day, promised_day  from package where package.end_day > package.promised_day; ";
				state = 0;

				printf("\n");
				printf("package_ID  company_name  start_day            delivered_day        promised_day\n");
				printf("----------  ------------  -------------------  -------------------  -------------------\n");

				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%10s  %12s %20s %20s %20s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
					}
					mysql_free_result(sql_result);
				}


				type13_num = _getch();
				system("cls");
				break;
			case '5':
				printf("---- TYPE 5 ----\n");
				printf("Generate the bill for each customer for the past month. Consider creating several types of bills.\n");
				printf("Which Year and Month? (ex. 2023 06 ) : ");
				cin >> type5_year >> type5_month;


				type5_sub = "select package.shipper_ID, shipper.address, bill.method, bill.billing_date, bill.price	from package, bill, shipper	where month(bill.billing_date) ='" + type5_month + "' and year(bill.billing_date) = '" + type5_year + "'and package.bill_ID = bill.bill_ID and package.shipper_ID = shipper.shipper_ID;";

				

				printf("\n");
				printf("customer_ID  customer_address      bill_method    billing_date          bil_price\n");
				printf("-----------  --------------------  -------------  --------------------  ----------\n");

				query = type5_sub.c_str();
				state = 0;


				state = mysql_query(connection, query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%11s  %20s  %13s  %20s  %10s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
					}
					mysql_free_result(sql_result);
				}


				type13_num = _getch();
				system("cls");
				break;
			case '0':
				return 0;
			default:
				break;
			}

		}

		

		mysql_close(connection);
		
	}

	return 0;
}







/*

	printf("------- SELECT QUERY TYPES -------\n\n");
	printf("\t1. TYPE 1\n");
	printf("\t2. TYPE 2\n");
	printf("\t3. TYPE 3\n");
	printf("\t4. TYPE 4\n");
	printf("\t5. TYPE 5\n");
	printf("\t6. TYPE 6\n");
	printf("\t7. TYPE 7\n");
	printf("\t0. QUIT\n");
	//printf("----------------------------------\n");
	printf("\n\n");
	printf("---- TYPE 5 ----\n\n");
	printf("** Find the top k brands by unit sales by the year**\n");
	printf(" Which K? : 3\n");

	return 0;

}
*/