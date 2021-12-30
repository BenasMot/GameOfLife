# 3. Conway gyvybės žaidimas
### **Užduotis:** parašykite programą, lygiagrečiai simuliuojančią ląstelių automatą, žinomą Conway „gyvybės žaidimo“ (Game of Life) pavadinimu.

- Aprašymas ir taisyklės: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life .

- Naudotojas gali rinktis begalinę arba periodinę žaidimo erdvę.

- Žaidimas baigiasi, kai langelių reikšmės nustoja keistis. Galimi atvejai:

	- Visi gyvi langeliai išnyksta.

	- Visi gyvi langeliai sudaro stabilų raštą.

	- Visi gyvi langeliai kas kelis ėjimus kartojasi (susiformuoja ribinis ciklas).

	  - Ciklų ilgį nusako programos parametras.

	- Gyvi langeliai keliauja į begalybę.

		- Ribinį ėjimų skaičių nusako programos parametras.

- Pagrindinė programos užduotis – nustatyti, per kiek ėjimų nuo pateiktos pradinės padėties
žaidimas baigiasi ir kokia yra galutinė padėtis.

	- Parodykite, kad programa su daugiau procesorių į šį klausimą atsako greičiau.

	- Jei paspartinti sprendimo nepavyksta, pabandykite nustatyti priežastis.

- Ar galite vizualizuoti rezultatus? O sprendimo eigą?

---
## **To-do:**
- Padaryti baigtinį ir begalinį žaidimo režimus
- Padaryti logiką su tikrinimais ląstelių gimimui ir mirimui
- Ėjimų skaičiavimas, bet čia lol, tsg count++
- Padaryti vizualizavimą tiek eigai, tiek pabaigai
- Išlygiagretinti programą
- Parodyti, kad paspartina, arba jeigu nepaspartina why
