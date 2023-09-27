#ifndef __TRACK_H
#define __TRACK_H

#include "sys.h"

#define A0  PGin(0)
#define A1  PGin(1)
#define A2  PGin(2)
#define A3  PGin(3) 
 
#define B0  PEin(10)
#define B1  PEin(11)
#define B2  PEin(12)
#define B3  PEin(13) 

#define QL  PEin(5)
#define QR  PEin(4)
#define HOU  PBin(14)
#define track_right PEin(6)
#define track_left  PEin(9)

void Track_delay(u16 time);
void xunji(u16 time);

void qian();

void track();
void track_1();
void track_back();

void test_qian();
void test_hou();
void test_hou1();
void test_right();
void test_left();

void turn180();
void turn180();
void turn(u8 drection);
void turn2();//×ª½Ç¼ì²â
void turn3();//×ª½Ç¼ì²â
void test_zhong();
void test_no();
void turn_adgust(u8 left,u8 right);
void test_go();
void test_left1();//houtuiyoubianÖÐµã¼ì²â
void turn_adust();

#endif

