create database wang;
use wang;

create table student	
(
	sno varchar(20) NOT NULL,
	sname varchar(50),
	age int,
	sex varchar(10),
	sclass varchar(100),
	primary key(sno),
	passwd varchar(20)
);
create table teacher
(
	tno varchar(20) primary key,
	tname varchar(50),
	tage int,
	passwd varchar(20)
);
create table course
(
	cno varchar(20) primary key,
	cname  varchar(50),
	Ccredit double
);
create table select_c
(
	sno varchar(20),
	cno varchar(20),
	grade DOUBLE,
	primary key(sno,cno),
	foreign key(sno) references student (sno),
	foreign key(cno) references course (cno) 
);
create table login
(
	lno varchar(20) primary key,
	num varchar(20) NOT NULL,
	Time varchar(50)
);

insert into course(cno,cname,Ccredit) values("10","Data structure",5);
insert into course(cno,cname,Ccredit) values("11","Algorithm",2);
insert into course(cno,cname,Ccredit) values("12","linux",5);
insert into course(cno,cname,Ccredit) values("13","C Language",3);
insert into course(cno,cname,Ccredit) values("14","Math",3);

insert into student(sno,sname,age,sex,sclass,passwd) values("2016013055", "zhongguolei", "19", "male", "xingxi163", "123456");
insert into select_c(sno,cno,grade) values("2016013055","10",85);

insert into teacher(tno,tname,tage,passwd) values("1001","yuxiao",20,"123456");
insert into teacher(tno,tname,tage,passwd) values("1002","zouqing",20,"123456");
insert into teacher(tno,tname,tage,passwd) values("1003","yujiantao",35,"123456");


