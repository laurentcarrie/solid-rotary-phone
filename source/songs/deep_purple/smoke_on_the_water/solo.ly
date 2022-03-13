\version "2.22.1"

song_tempo = 114

% Bb
ma = {

}

mg = {
    <g,\6 d\5 g\4>8
    <g,\6 d\5 g\4>8
    <g,\6 d\5 g\4>8
    r8
    <g,\6 d\5 g\4>8
    <g,\6 d\5 g\4>8
    <g,\6 d\5 g\4>8
    r8
}
mc = {
    <c\5 g\4 c'\3>8
    <c\5 g\4 c'\3>8
    <c\5 g\4 c'\3>8
    r8

    <c\5 g\4 c'\3>8
    <c\5 g\4 c'\3>8
    <c\5 g\4 c'\3>8
    r8
}
mf = {
    <f,\6 c\5 f\4>8
    <f,\6 c\5 f\4>8
    <f,\6 c\5 f\4>8
    r8
    <f,\6 c\5 f\4>8
    <f,\6 c\5 f\4>8
    <f,\6 c\5 f\4>8
    r8
}

lignea = {
    \mg | \mg | \mc | \mg |
}

ligneb = {
    \mc | \mc | \mf | \mf |
}



rhythm = {
\lignea
\lignea
\lignea
\lignea
\ligneb
}

lead = {
  \absolute  {
    \override Score.SpacingSpanner.shortest-duration-space = #4.0

    \set Score.currentBarNumber = #0

    % mes1
    r4 r4 r4 d'8\4 f'8\3
    |

    % mes 2
    g'2\3 r4 \myrelease d''16\2 c''4\2
    |

    % mes 3
    bes'8\2  g'8~\3 g'4\3 c''8\2 r8 r8 d'8\4
    |

    % mes 4
    f'8\3 g'8\3 bes'8\2 \mypull bes'16\2 c''8~\2 c''4\2 bes'8\2 a'8\2
    |

    % mes 5
    g'8\2 a'8\2 \times 2/3 { g'16\2 a'16\2 g'16\2 } f'8\3 g'8\2 f'8\3 dis'8\3 f'8\3
    |

    % mes 6
    f'8\3 g'8\2 fis'8\3 g'8~\2 \mypull f'16\3 g'4\3 r8 g'8\2
    |

    % mes 7
    bes'8\2 \mypull bes'16\2 c''8\2 bes'8\2 \mypull bes'16\2 c''8~\2 c''8\2 c''8\1 g'8\2 bes'8\2
    |

    % mes 8
    \mypull fis'32\3 g'16\3 g'16\2 c''16\1 bes'16\2
    a'16\2 g'16\2 ges'16\3  f'16\3
    ees'16\3 c'16\4 f'16\3 ees'16\3
    d'16\3 c'16\4 bes16\4 a16\4
    |

    % mes 9
    g8\4 bes8\4 a8\4 c'8\3 bes8\4 ees'8\3 d'8\3 c'8\3
    |

    % mes 10
    \mypull bes8\3 c'4~\3 c'4\3 c'8\3 bes8\3 a8\3 bes8\3

    % mes 11
    a8\3 bes8\3 a8\3 g8~\3 g2\3

    % mes 12
    \mypull c'16\3 d'16\3 d'16\2 g'16\1  \mypull f'16\2 g'16\2
    g'\1 g'\1 f'\2 e'\2
    d'\2 des'\3 c'\3 bes\3
    \times 2/3 { g8\4 c'8\3 bes8\3 }
    |

    % mes 13
    \times 2/3 { \mypull c'16\3 d'4\3 \mypull c'16\3 d'4\3 \mypull c'16\3 d'4\3 }
    \mypull c'16\3 d'4\3
    d'8\3 f'8\2
    |

    % mes 14
    g'8\2 d'8\3 f'8\2 g'8\2  b'8\1 \mypull c''16\1 c''4

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
