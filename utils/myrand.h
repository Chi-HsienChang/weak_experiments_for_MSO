/***************************************************************************
                          myrand.h  -  description
                             -------------------
    begin                : Aug 24 2001
    copyright            : (C) 2001 by Tian-Li Yu
    email                : tianliyu@illigal.ge.uiuc.edu
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MYRAND_H
#define MYRAND_H


/**
  *@author Tian-Li Yu
  */

#include "mt19937ar.h"


class MyRand
{
public:
  MyRand (int seed=0);
  ~MyRand ();

  bool flip (double prob = 0.5);

  /** From [a,b) */
  double uniform (double a, double b);

  /** From [0,1) */
  double uniform ();

  /** Standard normal distribution */
  double normal ();
  /** Normal distribution with mean and standard deviation */
  double normal (double mean, double std);
  /** No descriptions */
  int uniformInt (int a, int b);
  /** No descriptions */
  void uniformArray (int *array, int num, int a, int b);

};


#endif
