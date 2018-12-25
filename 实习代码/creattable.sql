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

insert into course(cno,cname,Ccredit) values("1001","shujujiegou",3);
insert into course(cno,cname,Ccredit) values("1002","suanfafenxi",3);
insert into course(cno,cname,Ccredit) values("1003","duomeiti",2.5);
insert into course(cno,cname,Ccredit) values("1004","banyiyuanli",3);

insert into teacher(tno,tname,tage,passwd) values("001","qw",2,"123456");
insert into teacher(tno,tname,tage,passwd) values("002","zq",10,"123456");
insert into teacher(tno,tname,tage,passwd) values("003","yx",35,"123456");
