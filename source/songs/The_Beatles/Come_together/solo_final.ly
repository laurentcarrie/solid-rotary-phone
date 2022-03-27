\version "2.22.1"
song_tempo = 90

ma = {

  d8 d8 c'8 b8~ b8 d8 c'8 a8~

}

mb = {

  a8 b16 r16 r4 r2

}



rhythm = {
  \ma | \mb | \ma |  \mb |
  \ma | \mb | \ma |  \mb |
  \ma | \mb | \ma |  \mb |
}

lead = {
  \relative c'' {
    \override Score.SpacingSpanner.shortest-duration-space = #4.0

    % mes 1
    %\grace c8\2^\markup { \char ##x2197   }
    %d1\2^\markup { \char ##x2197 }
    \mypull c8\2 d1\2
    |
    % mes 2
    r2
    r8
    %g8\1^\markup { \char ##x2197  }
    \mypull f16 g8
    %g16\1^\markup { \char ##x2197  }
    \mypull f16 g16
    \myrelease g16\1 f16\1
    d8\1
    |
    % mes 3
    \mypull c16\2 d1\2
    |
    % mes 4
    r2
    r8
    f,8\3
    \mypull g16\3 a16\3
    \myrelease a16\3 g16\3
    f8\3
    |
    % mes 5
    \mypull c'16\2 d1\2
    |
    % mes 6
    r2
    r8
    d8\1
    \mypull f16\1 g16\1
    \myrelease g16\1 f16\1
    d8\1
    |
    % mes 7
    \mypull c16\2 d1\2
    |
    % mes 8
    r2
    r8
    a8\2
    \mypull c16\2 d16\2
    \myrelease d16\2 c16\2
    a8\2
    |
    % mes 9
    \mypull g'16\1 a1\1
    |
    % mes 10
    r2
    r8
    \mypull g16\1 a8\1
    \mypull g16\1 a16\1
    \myrelease a16\1 g16\1
    f8\1
    |
    % mes 11
    \mypull g16\1 a1\1
    |
    % mes 12
    r2
    r8
    a8\1
    \mypull c16\1 d16\1
    \myrelease d16\1 c16\1
    a8\1
    |
    % mes 13
    \mypull c16\1 d1\1
    |
    % mes 14
    r2
    r8
    a8\1
    \mypull c16\1 d16\1
    \myrelease d16\1 c16\1
    a8\1
    % mes 15
    \mypull c16\1 d1\1
    % mes 16
    r2
    r8
    f,8\1
    \mypull g16\1 a16\1
    g16\1
    f8\1

    % mes 17
    \mypull g16\1 a1\1

    % mes 18
    r2
    r8
    f,8\3
    \mypull g16\3 a16\3
    g16\3
    f8\3

    % mes 19
    \mypull c'16\2 d1\2

    % mes 20
    r2
    r8
    \mypull f16\1 g8\1
    \mypull f16\1 g16\1
    f16\1
    d8\1

    % mes 21
    \mypull c16\2 d1\2

  }
}

drumbar =  \drummode {  bd4 sn4  bd4 sn4 }

drumbars = {
  \drumbar |   \drumbar |  \drumbar |  \drumbar |
  \drumbar |   \drumbar |  \drumbar |  \drumbar |
  \drumbar |   \drumbar |  \drumbar |  \drumbar |
  \drumbar |   \drumbar |  \drumbar |  \drumbar |
  \drumbar |   \drumbar |  \drumbar |  \drumbar |
  \drumbar

}


drumbarhh =  \drummode {
  hihat8
  hihat8
  hihat8
  hihat8
  hihat8
  hihat8
  hihat8
  hihat8
}

drumbarshh = {
  \drumbarhh |  \drumbarhh |  \drumbarhh |  \drumbarhh |
  \drumbarhh |  \drumbarhh |  \drumbarhh |  \drumbarhh |
  \drumbarhh |  \drumbarhh |  \drumbarhh |  \drumbarhh |
  \drumbarhh |  \drumbarhh |  \drumbarhh |  \drumbarhh |
  \drumbarhh |  \drumbarhh |  \drumbarhh |  \drumbarhh |
  \drumbarhh

}
