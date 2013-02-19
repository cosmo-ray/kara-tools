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

#define	VLC	0
#define	MPLAYER	1

template<int i = MPLAYER>
QString  getPlayerCmd();

template<>
QString  getPlayerCmd<VLC>();

void	 initRand();

void    toWinPath(QString &path);

void	execPlaylist(const QString &player, const QString &listKara);

#endif
