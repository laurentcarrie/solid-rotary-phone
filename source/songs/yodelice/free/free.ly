\version "2.20.0"

song_tempo = 100

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

drumbars =  \drummode {  bassdrum4 hihat4  bassdrum hihat }
drumbarshh = \drummode { r1 }

lead = {
    r1
}