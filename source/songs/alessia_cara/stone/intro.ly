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

    \override Score.SpacingSpanner.shortest-duration-space = #4.0
  \set Score.currentBarNumber = #0

  \set Score.barNumberVisibility = #all-bar-numbers-visible
    % mes 0
    r2 fis'8\3 gis'8\2 fis'8\3 cis'8\4  |

    \set Score.currentBarNumber = #1
    % mes 1
    e'4\3 r4 e'8\3 e'8\3 r8 e'8\3  |

    % mes 2
    r2 fis'8\3 gis'8\2 fis'8\3 cis'8\4  |

    % mes 3
    e'4\3 r4 e'8\3 e'8\3 r8 e'8\3  |

    % mes 4
    r2 fis'8\3 gis'8\2 fis'8\3 cis'8\4  |

    % mes 5
    e'4\3 r4 e'8\3 e'8\3 r8 e'8\3  |

    % mes 6
    r2 fis'8\3 gis'8\2 fis'8\3 cis'8\4  |

    % mes 7
    e'2\3 r8 fis'8\3 r8 e'8\3 |

    % mes 8
    dis'4\3 r4 r2


}

drumbar =  \drummode {  bd4 sn4  bd4 sn4 }

drumbars = {
  \repeat unfold 9 { \drumbar | }

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


song_chords = \chordmode {
r1 |
a1 | a1 | cis1:m | cis1:m |
a1 | a1 | cis1:m | b1 |

}

