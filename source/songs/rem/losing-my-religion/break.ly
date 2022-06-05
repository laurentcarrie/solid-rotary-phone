\version "2.20.0"
song_tempo = 90

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
  \relative c'' {
    \override Score.SpacingSpanner.shortest-duration-space = #4.0

    % mes 1
    r8 a,8\4 c8\3 a8\4 d4\3 r4 |
    % mes 2
    r8 e8\2 d8\3 c8\3 a8\4 r8 r4 |
    % mes 3
    r8 a8\4 c\3 d8\3 e8\2 r8 r4 |
    % mes 4
    r8 e8\2 d8\3 c\3 a8\4 r8 r4 |

  }
}

drumbar =  \drummode {  bd4 sn4  bd4 sn4 }

drumbars = {
  \repeat unfold 4 { \drumbar | }

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

}
