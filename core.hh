#ifndef	CORE_HH
#define	CORE_HH

#include	<stdio.h>
#include	<string>
#include	<iostream>

#ifdef	WIN32
#define	SLASH	'\\'
#else
#define	SLASH	'/'
#endif

QString  getPlayerCmd();
void	 initRand();


void	execPlaylist(const QString &player, const QString &listKara);

#endif
