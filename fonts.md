utiliser birdfont pour visualiser les fonts

charger une lettre depuis comic
l'exporter en svg

puis la charger sous birdfont, la modifier et sauvgarder 
toute la fonte

enfin charger la font avec fontbook

linux
-----
sur linux, pas l'air de marcher, meme avec :
    font-manager --install ...

la fonte est installée, on la voit mais lualatex ne la voit pas

apparemment la solution est de copier les fontes :

    rm -rf ~/.texlive*
    mkdir -p ~/.fonts
    cp source/style/*.ttf ~/.fonts


