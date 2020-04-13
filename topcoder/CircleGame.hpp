#include <string>
#include <iostream>
#include <cctype>


class CircleGame
{
    int map(char c)
    {
        if (std::isdigit(c))
            return static_cast<int>(c);

        switch (c)
        {
        case 'A':
            return 1;
        case 'T':
            return 10;
        case 'J':
            return 11;
        case 'Q':
            return 12;
        case 'K':
            return 13;
        
        default:
            return 0;
        }
    }
public:
    int cardsLeft(std::string deck)
    {
        bool wasChanged = false;
        do 
        {
            wasChanged = false;
            for(int i=0; i<deck.size(); ++i)
            {
                int c1 = map(deck[i]);
                if (c1 == 13)
                {;
                    wasChanged = true;
                    deck.erase(i, 1);   
                    --i;
                    continue;
                }
                int c2 = map(deck[(i+1) % deck.size()]);
                if ( (c1+c2)==13 )
                {
                    wasChanged = true;
                    deck.erase(i, 1);
                    if ( (i % deck.size()) == 0 )
                    {
                        deck.erase(0, 1);
                        break;
                    }
                    else
                    {
                        deck.erase(i, 1);
                    }
                    --i;
                }
            }
        } while (wasChanged);

        return deck.size();
    }

};
// SRM 148 DIV 1 250