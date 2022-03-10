\version "2.22.1"
song_tempo = 123

\include "../../common/macros.ly"


ma = {
  < a,e  >4
  < a,e  >4
  < a,e  >4
  < a,e  >4



}


mcis = {
  < cis gis >4
  < cis gis >4
  < cis gis >4
  < cis gis >4

}


mb = {

  < b, fis b dis' > 4
  r4
  r2

}



rhythm = {
 r1 |
 \ma | \ma | \mcis | \mcis |
 \ma | \ma | \mcis | \mb |

}

lead = {
  \relative c' {
    \override Score.SpacingSpanner.shortest-duration-space = #4.0

    % mes
    r2 fis8\3 gis8\2 fis8\3 cis8\4 |
    % mes 1
    \set Score.currentBarNumber = #1
    e2\3 e8\3 e8\3  r8 e8~\3    |
    % mes 2
    e8\3 r8 r4 fis8\3 gis8\2 fis8\3 cis8\4 |
    % mes 3
    e2\3 e8\3 e8\3  r8 e8~\3    |
    % mes 4
    e8\3 r8 r4 fis8\3 gis8\2 fis8\3 cis8\4 |
    % mes 5
    e2\3 e8\3 e8\3  r8 e8~\3    |
    % mes 6
    e8\3 r8 r4 fis8\3 gis8\2 fis8\3 cis8\4 |
    % mes 7
    e4\3  r4 r8. fis8\3  r16 e8\3 |
    % mes 8
    dis4\3  r4 r4
  }
}

drumbar =  \drummode {  bd4 sn4  bd4 sn4 }

drumbars = {
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

}
