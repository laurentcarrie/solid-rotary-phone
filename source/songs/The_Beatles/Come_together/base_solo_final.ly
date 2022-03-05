\version "2.22.1"
song_tempo = 88

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
    \grace c8\2^\markup { \char ##x2197   }
    d1\2^\markup { \char ##x2197 }
    |
    % mes 2
    r2
    r8
    g8\1^\markup { \char ##x2197  }
    g16\1^\markup { \char ##x2197  }
    f16\1
    d8\1
    |
    % mes 3
    d1\2
    |
    % mes 4
    r2
    r8
    f,8\3
    a16\3
    g16\3
    f8\3
    |
    % mes 5
    d'1\2
    |
    % mes 6
    r2
    r8
    d8\1
    g16\1
    f16\1
    d8\1
    |
    % mes 7
    d1\2
    |
    % mes 8
    r2
    r8
    a8\2
    d16\2
    c16\2
    a8\2
    |
    % mes 9
    a'1\1
    |
    % mes 10
    r2
    r8
    a8\1
    a16\1
    g16\1
    f8\1
    |
    % mes 11
    a1\1
    |
    % mes 12
    r2
    r8
    a8\1
    d16\1
    c16\1
    a8\1
    |
    % mes 13
    d1\1
    |
    % mes 14
    r2
    r8
    a8\1
    d16\1
    c16\1
    a8\1
    % mes 15
    d1\1
    % mes 16
    r2
    r8
    f,8\1
    a16\1
    g16\1
    f8\1
    % mes 17
    a1\1
    % mes 18
    r2
    r8
    f,8\3
    a16\3
    g16\3
    f8\3
    % mes 19
    d'1\2
    % mes 20
    r2
    r8
    g8\1
    g16\1
    f16\1
    d8\1
    % mes 21
    d1\2

  }
}

drumbar =  \drummode {  bd4 sn4  bd4 sn4 }

drumbars = {
  \drumbar |   \drumbar |  \drumbar |  \drumbar |
  \drumbar |   \drumbar |  \drumbar |  \drumbar |
  \drumbar |   \drumbar |  \drumbar |  \drumbar |
  \drumbar |   \drumbar |  \drumbar |  \drumbar |
  \drumbar |   \drumbar |  \drumbar |  \drumbar |

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

}
