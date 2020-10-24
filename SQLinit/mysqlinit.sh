#!/bin/sh
##################################
USER="root"
PASSWORD="zncg123456"
DATABASE="earthquake_monitor"
TABLE1="ontime_data"
TABLE2="data_message"
TABLE3="data_min"
TABLE4="data_max"
TABLE5="data_ave"
TABLE6="data_send"
##################################
#create database
create_db_sql="CREATE DATABASE $DATABASE"
mysql -u${USER} -p${PASSWORD} -e"${create_db_sql}"
[ $? -eq 0 ]&& echo "created db success" || echo "db already exist"

#create table
create_table1_sql="CREATE TABLE ${TABLE1} (timestrap DOUBLE NOT NULL,value DOUBLE NULL,PRIMARY KEY (timestrap))"
mysql -u${USER} -p${PASSWORD} -D${DATABASE} -e"${create_table1_sql}"
[ $? -eq 0 ]&& echo "created table1 success" || echo "Table1 already exist"

create_table2_sql="CREATE TABLE ${TABLE2} (id INT NOT NULL AUTO_INCREMENT,message_introduction VARCHAR(45) NULL,message_int_content INT NULL,message_double_content DOUBLE NULL,PRIMARY KEY (id))"
mysql -u${USER} -p${PASSWORD} -D${DATABASE} -e"${create_table2_sql}"
[ $? -eq 0 ]&& echo "created table2 success" || echo "Table2 already exist"

create_table3_sql="CREATE TABLE ${TABLE3} (id INT NOT NULL AUTO_INCREMENT,min_data_value DOUBLE NULL,PRIMARY KEY (id))"
mysql -u${USER} -p${PASSWORD} -D${DATABASE} -e"${create_table3_sql}"
[ $? -eq 0 ]&& echo "created table3 success" || echo "Table3 already exist"

create_table4_sql="CREATE TABLE ${TABLE4} (id INT NOT NULL AUTO_INCREMENT,max_data_value DOUBLE NULL,PRIMARY KEY (id))"
mysql -u${USER} -p${PASSWORD} -D${DATABASE} -e"${create_table4_sql}"
[ $? -eq 0 ]&& echo "created table4 success" || echo "Table4 already exist"

create_table5_sql="CREATE TABLE ${TABLE5} (id INT NOT NULL AUTO_INCREMENT,ave_data_value DOUBLE NULL,PRIMARY KEY (id))"
mysql -u${USER} -p${PASSWORD} -D${DATABASE} -e"${create_table5_sql}"
[ $? -eq 0 ]&& echo "created table5 success" || echo "Table5 already exist"

create_table6_sql="CREATE TABLE ${TABLE6} (timestrap DOUBLE NOT NULL,tunnel_ID VARCHAR(1) NULL,max_value_1s FLOAT NULL,min_value_1s FLOAT NULL,max_value_5s FLOAT NULL,min_value_5s FLOAT NULL,max_value_30s FLOAT NULL,min_value_30s FLOAT NULL,ave_value_3s FLOAT NULL,ave_value_60s FLOAT NULL,ave_ratio FLOAT NULL,sensor_status FLOAT NULL,PRIMARY KEY (timestrap))"
mysql -u${USER} -p${PASSWORD} -D${DATABASE} -e"${create_table6_sql}"
[ $? -eq 0 ]&& echo "created table6 success" || echo "Table6 already exist"

#insert data
insert_sql="INSERT INTO ${TABLE2} (id, message_introduction, message_int_content, message_double_content) VALUES (1, 'total row of ontime signal', 0, 0)"
mysql -u${USER} -p${PASSWORD} -D${DATABASE} -e"${insert_sql}"
[ $? -eq 0 ]&& echo "data insert success" || echo "data already exist"
