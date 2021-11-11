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
    a'2~
    a8
    a8
    a16
    g16
    f8
    |
    a1
    |
    a2~
    a8
    a8
    a16
    g16
    f8
    |
    e2~\2
    e8\2
    c8\2
    e16\2
    d16\2
    c8\2
    |
    a'1\1

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
