\version "2.20.0"

\paper {
  indent = 0\mm
  line-width = 210\mm
  oddHeaderMarkup = ""
  evenHeaderMarkup = ""
  oddFooterMarkup = ""
  evenFooterMarkup = ""
}



gm = {
  r8
  < g d' g' bes' d'' g'' >8
  r8
  < g d' g' bes' d'' g'' >8
  r8
  < g d' g' bes' d'' g'' >8
  r8
  < g d' g' bes' d'' g'' >8

}

cm = {
  r8
  < c' g'  c'' ees'' g''>8
  r8
  < c' g'  c'' ees'' g''>8
  r8
  < c' g'  c'' ees'' g''>8
  r8
  < c' g'  c'' ees'' g''>8

}

rhythm = {
  \gm | \cm | \cm | \gm |
  \gm | \cm | \cm | \gm


}

drumbar =  \drummode {  bassdrum4 hihat4  bassdrum hihat }

\score {

  <<

    \new DrumStaff {

      \drumbar |
      \drumbar |
      \drumbar |
      \drumbar |
      \drumbar |
      \drumbar |
      \drumbar |
      \drumbar |
      \drumbar |
      \drumbar |
      \drumbar |
      \drumbar |
      \drumbar |
      \drumbar |



    }


    \new Staff {
      \tempo 4 = 90
      \override Score.BarNumber.break-visibility = ##(#t #t #t)
      %\set TabStaff.stringTunings = #custom-tuning
      \rhythm
    }



  >>
  \layout {}

  \midi {}
}
