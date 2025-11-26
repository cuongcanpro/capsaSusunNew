#pragma once
#ifndef TienlenCard_h__
#define TienlenCard_h__

// Card Suit:
#define ES_HEART 4
#define ES_DIAMOND 3
#define ES_CLUB 2
#define ES_SPADE 1

class TienlenCard
{
public:
	TienlenCard(void)
	{

	}
	~TienlenCard(void)
	{
	}
    
    int ID;
        
   
    int GetNumber()
    {
      return (ID / 4 + 3);
    }
   
    int GetSuit()
    {
      return (ID %4 + 1);
    }
    /**
     * so sanh voi quan bai khac
     * @param card
     * @return 
     * 			-1: Nho hon
     * 			1: Lon hon
     *			0: Bang nhau
     */
    
    int compare(TienlenCard* card){
    	if(GetNumber()>card->GetNumber()){
    		return 1;
    	}else if(GetNumber()<card->GetNumber()){
    		return -1;
    	}else {
    		if(GetSuit()>card->GetSuit()){
        		return 1;
        	}else if(GetSuit()<card->GetSuit()){
        		return -1;
        	}else {
        		return 0;
        	}
    	}
    }

	void setCard(int n, int s) {
		// Convert code Binh
		ID = (n - 3) * 4 + (s - 1);
	}
};
#endif // TienlenCard_h__

