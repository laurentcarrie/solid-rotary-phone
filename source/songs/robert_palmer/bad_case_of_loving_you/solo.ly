\version "2.20.0"
song_tempo = 140

ma = {

  < d a d' f' >4
  < d a d' f' >4
  < d a d' f' >4
  < d a d' f' >4

}

mb = {

  < a, e a cis >4
  < a, e a cis >4
  < a, e a cis >4
  < a, e a cis >4


}


mc = {

  < e, b, e gis >4
  < e, b, e gis >4
  < e, b, e gis >4
  < e, b, e gis >4


}


md = {

  < a e >4
  < a e >4
  < a e >4
  < a e >4


}



rhythm = {
  \ma | \mb | \mc |  \md |

}

lead = {

    \override Score.SpacingSpanner.shortest-duration-space = #4.0
    \set Score.currentBarNumber = #69

    \set Score.barNumberVisibility = #all-bar-numbers-visible
    % mes 69
    \mypull a'8\2 b'1\2 |

    % mes 70
    r4
    \mypull a'8\2 b'4\2
    \mypull a'8\2 b'4\2
    g'4\2
    |

    % mes 71
    \mypull a'8\2 b'1~\2
    |

    % mes 72
    b'1\2
    |

    % mes 73
    \mypull a'8\2 b'1\2 |


    % mes 74
    r4
    \mypull a'8\2 b'4\2
    \mypull a'8\2 b'4\2
    g'8\2 e'8\3
    |

    % mes 75
    <g'\3 b'\2>8 r8
    r4
    <g'\3 b'\2>8 r8
    r8  <g'\3 b'\2>8
    |

    % mes 76
    r8 a'8\3
    e''8\2 fis''8\2
    e''8\2  d''8\2
    cis''8\2 e'8\4
    |

    % mes 77
    a'4\3
    b'8\3 a'8\3
    b'8\3 \mypull b'8\3 cis''8\3
    e''8\2 cis''8~\3

    % mes 78
    \myrelease cis''8\3 b'8\3 a'8\3
    b'4\3
    a'4\3
    b'8\3 d''8\2
    |

    % mes 79
    dis''8\2 e''8\2
    \mypull e''8\2 fis''8\2  \myrelease fis''8\2 e''8\2
    d''8\2 dis''8\2
    b'8\3 fis'8\4
    |

    % mes 80
    b'4\3
    a'8\3 fis'8\4
    b'8\3 r8
    ais'8\3 r8
    |

    % mes 81
    a'1\3
    |

    % mes 82
    r8 a,8\5
    cis8\5 e8\4
    g8\4 fis8\4
    e8\4 cis8\5

    % mes 83
    e,1\6



}

drumbar =  \drummode {  bd4 sn4  bd4 sn4 }

drumbars = {
  \repeat unfold 14 { \drumbar | }

}


drumbarhh =  \drummode {
    \repeat unfold 8 { hihat8 }
}

drumbarshh = {
  \repeat unfold 14 { \drumbarhh | }

}


song_chords = \chordmode {
e1 | e1 | e1 | e1 |
e1 | e1 | e1 | e1 |
a1 | a1 | b1 | b1 |
a1 | a1 |
}

