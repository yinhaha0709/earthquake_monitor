#!/bin/sh
##################################
USER="root"
PASSWORD="zncg123456"
DATABASE="vibration"
TABLE1="ontime_data"
TABLE2="data_message"
TABLE3="data_min"
TABLE4="data_max"
TABLE5="data_ave"
#TABLE3_2="data_min2"
#TABLE4_2="data_max2"
#TABLE5_2="data_ave2"
#TABLE3_3="data_min3"
#TABLE4_3="data_max3"
#TABLE5_3="data_ave3"
#TABLE3_4="data_min4"
#TABLE4_4="data_max4"
#TABLE5_4="data_ave4"
#TABLE3_5="data_min5"
#TABLE4_5="data_max5"
#TABLE5_5="data_ave5"
#TABLE3_6="data_min6"
#TABLE4_6="data_max6"
#TABLE5_6="data_ave6"
TABLE6="data_send"
##################################
#drop database
drop_db_sql="DROP DATABASE $DATABASE"
mysql -u${USER} -p${PASSWORD} -e"${drop_db_sql}"
[ $? -eq 0 ]&& echo "drop db success" || echo "drop db failed"

#create database
create_db_sql="CREATE DATABASE $DATABASE"
mysql -u${USER} -p${PASSWORD} -e"${create_db_sql}"
[ $? -eq 0 ]&& echo "created db success" || echo "db already exist"

#create table
create_table1_sql="CREATE TABLE ${TABLE1} (timestrap DOUBLE NOT NULL,value1 DOUBLE NULL,value2 DOUBLE NULL,value3 DOUBLE NULL,value4 DOUBLE NULL,value5 DOUBLE NULL,value6 DOUBLE NULL,PRIMARY KEY (timestrap))"
mysql -u${USER} -p${PASSWORD} -D${DATABASE} -e"${create_table1_sql}"
[ $? -eq 0 ]&& echo "created table1 success" || echo "Table1 already exist"

create_table2_sql="CREATE TABLE ${TABLE2} (id INT NOT NULL AUTO_INCREMENT,message_introduction VARCHAR(45) NULL,message_int_content INT NULL,message_double_content DOUBLE NULL,PRIMARY KEY (id))"
mysql -u${USER} -p${PASSWORD} -D${DATABASE} -e"${create_table2_sql}"
[ $? -eq 0 ]&& echo "created table2 success" || echo "Table2 already exist"

create_table3_sql="CREATE TABLE ${TABLE3} (id INT NOT NULL AUTO_INCREMENT,min_data_value1 DOUBLE NULL,min_data_value2 DOUBLE NULL,min_data_value3 DOUBLE NULL,min_data_value4 DOUBLE NULL,min_data_value5 DOUBLE NULL,min_data_value6 DOUBLE NULL,PRIMARY KEY (id))"
mysql -u${USER} -p${PASSWORD} -D${DATABASE} -e"${create_table3_sql}"
[ $? -eq 0 ]&& echo "created table3 success" || echo "Table3 already exist"

create_table4_sql="CREATE TABLE ${TABLE4} (id INT NOT NULL AUTO_INCREMENT,max_data_value1 DOUBLE NULL,max_data_value2 DOUBLE NULL,max_data_value3 DOUBLE NULL,max_data_value4 DOUBLE NULL,max_data_value5 DOUBLE NULL,max_data_value6 DOUBLE NULL,PRIMARY KEY (id))"
mysql -u${USER} -p${PASSWORD} -D${DATABASE} -e"${create_table4_sql}"
[ $? -eq 0 ]&& echo "created table4 success" || echo "Table4 already exist"

create_table5_sql="CREATE TABLE ${TABLE5} (id INT NOT NULL AUTO_INCREMENT,ave_data_value1 DOUBLE NULL,ave_data_value2 DOUBLE NULL,ave_data_value3 DOUBLE NULL,ave_data_value4 DOUBLE NULL,ave_data_value5 DOUBLE NULL,ave_data_value6 DOUBLE NULL,PRIMARY KEY (id))"
mysql -u${USER} -p${PASSWORD} -D${DATABASE} -e"${create_table5_sql}"
[ $? -eq 0 ]&& echo "created table5 success" || echo "Table5 already exist"

create_table6_sql="CREATE TABLE ${TABLE6} (timestrap DOUBLE NOT NULL,max_value1_1s FLOAT NULL,min_value1_1s FLOAT NULL,max_value1_5s FLOAT NULL,min_value1_5s FLOAT NULL,max_value1_30s FLOAT NULL,min_value1_30s FLOAT NULL,ave_value1_3s FLOAT NULL,ave_value1_60s FLOAT NULL,ave_ratio1 FLOAT NULL,sensor_status1 FLOAT NULL,max_value2_1s FLOAT NULL,min_value2_1s FLOAT NULL,max_value2_5s FLOAT NULL,min_value2_5s FLOAT NULL,max_value2_30s FLOAT NULL,min_value2_30s FLOAT NULL,ave_value2_3s FLOAT NULL,ave_value2_60s FLOAT NULL,ave_ratio2 FLOAT NULL,sensor_status2 FLOAT NULL,max_value3_1s FLOAT NULL,min_value3_1s FLOAT NULL,max_value3_5s FLOAT NULL,min_value3_5s FLOAT NULL,max_value3_30s FLOAT NULL,min_value3_30s FLOAT NULL,ave_value3_3s FLOAT NULL,ave_value3_60s FLOAT NULL,ave_ratio3 FLOAT NULL,sensor_status3 FLOAT NULL,max_value4_1s FLOAT NULL,min_value4_1s FLOAT NULL,max_value4_5s FLOAT NULL,min_value4_5s FLOAT NULL,max_value4_30s FLOAT NULL,min_value4_30s FLOAT NULL,ave_value4_3s FLOAT NULL,ave_value4_60s FLOAT NULL,ave_ratio4 FLOAT NULL,sensor_status4 FLOAT NULL,max_value5_1s FLOAT NULL,min_value5_1s FLOAT NULL,max_value5_5s FLOAT NULL,min_value5_5s FLOAT NULL,max_value5_30s FLOAT NULL,min_value5_30s FLOAT NULL,ave_value5_3s FLOAT NULL,ave_value5_60s FLOAT NULL,ave_ratio5 FLOAT NULL,sensor_status5 FLOAT NULL,max_value6_1s FLOAT NULL,min_value6_1s FLOAT NULL,max_value6_5s FLOAT NULL,min_value6_5s FLOAT NULL,max_value6_30s FLOAT NULL,min_value6_30s FLOAT NULL,ave_value6_3s FLOAT NULL,ave_value6_60s FLOAT NULL,ave_ratio6 FLOAT NULL,sensor_status6 FLOAT NULL,PRIMARY KEY (timestrap))"
mysql -u${USER} -p${PASSWORD} -D${DATABASE} -e"${create_table6_sql}"
[ $? -eq 0 ]&& echo "created table6 success" || echo "Table6 already exist"

#insert data
insert1_sql="INSERT INTO ${TABLE2} (id, message_introduction, message_int_content, message_double_content) VALUES (1, 'ontime_status', 0, 0)"
insert2_sql="INSERT INTO ${TABLE2} (id, message_introduction, message_int_content, message_double_content) VALUES (2, 'ftp_status', 1, 0)"
insert3_sql="INSERT INTO ${TABLE2} (id, message_introduction, message_int_content, message_double_content) VALUES (3, 'event_num', 16, 0)"

mysql -u${USER} -p${PASSWORD} -D${DATABASE} -e"${insert1_sql}"
[ $? -eq 0 ]&& echo "data1 insert success" || echo "data1 already exist"

mysql -u${USER} -p${PASSWORD} -D${DATABASE} -e"${insert2_sql}"
[ $? -eq 0 ]&& echo "data2 insert success" || echo "data2 already exist"

mysql -u${USER} -p${PASSWORD} -D${DATABASE} -e"${insert3_sql}"
[ $? -eq 0 ]&& echo "data3 insert success" || echo "data3 already exist"
