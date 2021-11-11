\version "2.20.0"

\paper {
  indent = 0\mm
  line-width = 210\mm
  oddHeaderMarkup = ""
  evenHeaderMarkup = ""
  oddFooterMarkup = ""
  evenFooterMarkup = ""
}



ma = {
  < d' a'>8
  < d' a'>
  < d' b'>
  < d' b'>
  < d' a'>8
  < d' a'>
  < d' b'>
  < d' b'>
}

mb = {
  < gis dis' gis' b' dis'' >
  < gis dis' gis' b' dis'' >
  < b fis' b' dis'  >
  < b fis' b' dis'  >
}

mc = {
  < e' gis' b' e'' >
  < e' gis' b' e'' >
  < gis dis' gis' b' dis'' >
  < gis dis' gis' b' dis'' >
}

md = {
  <a e' a' cis' >
  <a e' a' cis' >
  <a e' a' cis' >
  <a e' a' cis' >
}


rhythm = {
  \ma \ma \ma \ma
  \ma \ma \ma \ma
}

lead = {
  \relative c'' {
    \override Score.SpacingSpanner.shortest-duration-space = #4.0
    g'2-\bendAfter #1
    r8
    g8-\bendAfter #1
    a8-\bendAfter #-1
    f16
    r16
    |
    (g8)-\bendAfter #5 a8
    |
    g2-\bendAfter #1
    r8
    g8-\bendAfter #1
    a8-\bendAfter #-1
    f16
    r16
    |
    (g8)-\bendAfter #5 a8
    |

    %c4-\bendAfter #5
    %c2-\bendAfter #-4.75
    %c2-\bendAfter #8.5
    %c2-\bendAfter #-6
  }
}

drumbar =  \drummode {  bassdrum4 hihat4  bassdrum hihat }

\score {

  <<

    \new DrumStaff {

      \drumbar |
      \drumbar |
      \drumbar |
      \drumbar |
      %      \drumbar |
      %      \drumbar |
      %      \drumbar |
      %      \drumbar |
      %      \drumbar |
      %      \drumbar |
      %      \drumbar |
      %      \drumbar |
      %      \drumbar |
      %      \drumbar |



    }


    %    \new Staff {
    %      \tempo 4 = 83
    %      \override Score.BarNumber.break-visibility = ##(#t #t #t)
    %     %\set TabStaff.stringTunings = #custom-tuning
    %      \rhythm
    %    }

    \new Staff	 {
      \clef "treble_8"
      \tempo 4 = 90
      \override Score.BarNumber.break-visibility = ##(#t #t #t)
      \lead
    }

    \new TabStaff {
      \tempo 4 = 90
      \tabFullNotation
      \override Score.BarNumber.break-visibility = ##(#t #t #t)
      \lead
    }



  >>
  \layout {}

  \midi {}
}
