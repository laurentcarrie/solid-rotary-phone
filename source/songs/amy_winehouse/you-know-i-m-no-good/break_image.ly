\version "2.22.0"

\paper {
  #(include-special-characters)
  indent = 0\mm
  line-width = 210\mm
  oddHeaderMarkup = ""
  evenHeaderMarkup = ""
  oddFooterMarkup = ""
  evenFooterMarkup = ""

  #(add-text-replacements!
    '(
       ("100" . "hundred")
       ("dpi" . "dots per inch")
       ))

}

\include "base_break.ly"


\score {

  <<

    %\new DrumStaff
    % <<
    %        \new DrumVoice { \voiceOne \drumbarshh }
%
%      \new DrumVoice { \voiceTwo \drumbars }
%      >>



%    \new Staff {
%      \clef "treble_8"
%      \tempo 4 = \song_tempo
%      \override Score.BarNumber.break-visibility = ##(#t #t #t)
%      \omit StringNumber
%      \rhythm
%    }



    \new TabStaff {
      \tempo 4 = \song_tempo
      \tabFullNotation
      \override Score.BarNumber.break-visibility = ##(#t #t #t)
      \lead
    }


  >>
  \layout {}


}
