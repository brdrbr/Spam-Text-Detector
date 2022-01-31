#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

/************  COMP201 ASSIGNMENT 2  ************/

//Berke Derin Berktay


float *calculate_tf(FILE *fp, char * word);

float calculate_idf(long totalNumber, long numberOccurrence);

int main(int argc, char *argv[])
{

    
    if (strcmp(argv[1], "calculate-tf") == 0) //frequencyAnalysis
    {
        //TODO:Task 1
        FILE *fp;
        
        char * word = argv[2];

        char line[1024];

        char *res;

        short totalHam, totalSpam = 0;

        long numberHam, numberSpam = 0;

        float tfS, tfHam = 0 ;

        short totalCount,totalNum = 0;
        fp = fopen("SMSSPamCollection.txt","r");
    
        while(fgets(line,sizeof(line),fp) != NULL){
            
            res = line;
            
            bool ham = 0;
            
            if(line[0] == 'h'){
                
                totalHam++;

                ham = 1;

            } else if(line[1] == 'p'){
                
                totalSpam++;

            }
            for(int i= 0; i < strlen(line); i++){ 
                
                res = strcasestr(res,word);
                
                if(res == NULL) break;

                if((res == line) || (!isalpha((unsigned char)res[-1]))){

                    res += strlen(word);
                
                    i += strlen(word);

                    if (!isalpha((unsigned char)*res)){
                        
                        if(ham){

                            numberHam++;

                        } else {

                            numberSpam++;
                        }
                        

                    }  

                }

                res++;
            }


        }

        fclose(fp);

        tfHam = ((float)numberHam / totalHam);
        tfS = ((float)numberSpam / totalSpam);

        if(tfHam == 0 && tfS == 0){

            printf("This word doesn't occur in the text.txt");
            //printf("\n Total Count: %d",totalCount);
                
        } else {
//            printf("\n Total Count: %d",totalCount);
            printf("\nTotal Ham: %d",totalHam);
            printf("\nWord in Ham: %d", numberHam);
            printf("\nCalculated tf value for this word: %.6f", tfHam);

            printf("\nTotal Spam: %d",totalSpam);
            printf("\nWord in Spam: %d",numberSpam);
            printf("\nCalculated tf value for this word: %.6f", tfS);

            if(tfHam >= tfS){

                printf("\nThis word is mostly used for non spam messages.");
            
            } else {
            
                printf("\nThis word is mostly used for spam messages.");
            
            }
        }
    }

    else if (strcmp(argv[1], "predict") == 0) //spamDetection
    {
        //TODO:Task 2
        
        int i,j;

        float scoreHam, scoreSpam = 0;

        for(j = 2; j <= 6;j++){

            FILE *fp;
            
            char line[1024];

            char *res;

            int  totalHam = 0, totalSpam = 0;

            int numberHam = 0, numberSpam = 0;

            float tfS = 0, tfHam = 0 ;

            int totalCount=0;
            
            int totalNum = 0;
            
            float idf = 0;

            char* wordz = argv[j];
            
            fp = fopen("SMSSPamCollection.txt","r");

            while(fgets(line,sizeof(line),fp) != NULL){
                
                totalNum++;
                
                res = line;

                bool ham = 0;
                
                if(line[0] == 'h'){
                    
                    totalHam++;

                    ham = 1;

                } else if(line[1] == 'p'){
                    
                    totalSpam++;

                    ham = 0;

                }
                for(int k = 0; wordz[k];k++){

                    wordz[k] = tolower(wordz[k]);

                }

                for(int l = 0; line[l];l++){

                    line[l] = tolower(line[l]);

                }

                for(int p= 0; p < strlen(line); p++){ 
                
                    res = strstr(res,wordz);
                
                    if(res == NULL) break;

                    if((res == line) || (!isalpha((unsigned char)res[-1]))){

                        res += strlen(wordz);
                    
                        p += strlen(wordz);

                        if (!isalpha((unsigned char)*res)){
                            
                            if(ham){

                                numberHam++;

                            } else {

                                numberSpam++;
                            }
                            

                        }  

                    }

                    res++;
                }


             
                for(int i = 0;i < strlen(line);i++){
                    
                    int g = i;
                     
                    if(wordz[0] == line[i]){

                        int m = 1;
                        
                        for( m = 1; m < strlen(wordz);m++){
                        
                            g++;

                            if(wordz[m] != line[g]){
                                
                                break;

                            } 
                            

                        } 
                        if(!isalpha(line[i-1]) && !isalpha(line[g+1]) && m == strlen(wordz)){
                            
                            totalCount++;

                            break;
                        }
            
                    }
                }
                

            }
             
            fclose(fp);

            tfHam = ((float)numberHam / totalHam);
            
            tfS = ((float)numberSpam / totalSpam);


            if(totalCount > 0){

                idf = logf(((float)(totalNum)/totalCount));

                scoreHam += tfHam*idf;

                scoreSpam += tfS*idf;

            }

            // printf("\nnumberHam %d", numberHam);
            // printf("\nnumberSpam %d", numberSpam);
            // printf("\ntotalHam %d", totalHam);
            // printf("\ntotalSpam %d", totalSpam);
            // printf("\ntotalCount %d", totalCount);
            //printf("\ntotalNum %d", totalNum);
        }
        
        
        printf("\nTotal tf-idf score from non spam messages for the sentence: %.6f", scoreHam);
        printf("\nTotal tf-idf score from spam messages for the sentence: %.6f", scoreSpam);

        if(scoreHam > scoreSpam){

            printf("\nThe sentence is not spam.");
        
        } else {
        
            printf("\nThe sentence is spam.");
        
        } 
    
    }

    else if (strcmp(argv[1], "predict-wo-stopwords") == 0) //stopWords
    {
        //TODO:Task Extra        
        int i,j;

        float scoreHam, scoreSpam = 0;

        for(j = 2; j <= 6;j++){

            FILE *fp;

            FILE *fp2;
            
            char line[1024];

            char *res;

            int  totalHam = 0, totalSpam = 0;

            int numberHam = 0, numberSpam = 0;

            float tfS = 0, tfHam = 0 ;

            int totalCount=0;
            
            int totalNum = 0;
            
            float idf = 0;

            char* wordz = argv[j];

            int lenSub = strlen(wordz);

            int lenStr = strlen(line);

            int stop = (lenStr - lenSub) + 1;

            int numOccurs = 0;

            fp2 = fopen("99webtools.txt","r");
            
            bool checker = true;

            while(fgets(line,sizeof(line),fp2) != NULL){


                if(strstr(line,wordz)){

                    printf("\n%s is a stop word, it is not used in tf-idf calculations.",wordz);

                    checker = false;

                    break;
                }
            }
            
            if(checker){
                
                fp = fopen("SMSSPamCollection.txt","r");

                while(fgets(line,sizeof(line),fp) != NULL){
                    
                    totalNum++;
                    
                    res = line;

                    bool ham = 0;
                    
                    if(line[0] == 'h'){
                        
                        totalHam++;

                        ham = 1;

                    } else if(line[1] == 'p'){
                        
                        totalSpam++;

                        ham = 0;

                    }
                    for(int k = 0; wordz[k];k++){

                        wordz[k] = tolower(wordz[k]);

                    }

                    for(int l = 0; line[l];l++){

                        line[l] = tolower(line[l]);

                    }

                    
                        for(int p= 0; p < strlen(line); p++){ 
                    
                        res = strstr(res,wordz);
                    
                        if(res == NULL) break;

                        if((res == line) || (!isalpha((unsigned char)res[-1]))){

                            res += strlen(wordz);
                        
                            p += strlen(wordz);

                            if (!isalpha((unsigned char)*res)){
                                
                                if(ham){

                                    numberHam++;

                                } else {

                                    numberSpam++;
                                }
                                

                            }  

                        }

                        res++;
                    }


                
                    for(int i = 0;i < strlen(line);i++){
                        
                        int g = i;
                        
                        if(wordz[0] == line[i]){

                            int m = 1;
                            
                            for( m = 1; m < strlen(wordz);m++){
                            
                                g++;

                                if(wordz[m] != line[g]){
                                    
                                    break;

                                } 
                                

                            } 
                            if(!isalpha(line[i-1]) && !isalpha(line[g+1]) && m == strlen(wordz)){
                                
                                totalCount++;

                                break;
                            }
                
                        }
                    }
                    

                }
                
                fclose(fp);

                tfHam = ((float)numberHam / totalHam);
                
                tfS = ((float)numberSpam / totalSpam);


                if(totalCount > 0){

                    idf = logf(((float)(totalNum)/totalCount));

                    scoreHam += tfHam*idf;

                    scoreSpam += tfS*idf;

                }

                

                
                // printf("\nnumberHam for %s: %d",wordz,numberHam);
                // printf("\nnumberSpam %d", wordz,numberSpam);
                // printf("\ntotalHam %d", wordz,totalHam);
                // printf("\ntotalSpam %d", wordz,totalSpam);
                // printf("\ntotalCount %d", wordz, totalCount);
                // printf("\ntotalNum %d", wordz, totalNum);
            }
        }
            
        
        
        printf("\nTotal tf-idf score from non spam messages for the sentence: %.6f", scoreHam);
        printf("\nTotal tf-idf score from spam messages for the sentence: %.6f", scoreSpam);

        if(scoreHam > scoreSpam){

            printf("\nThe sentence is not spam.");
        
        }else if(scoreHam == 0 && scoreSpam == 0){
            
            printf("\nTf-idf scores are found to be 0, spam detection failed!");
        } else {
        
            printf("\nThe sentence is spam.");
        
        } 
    }

    else
    {
        printf("Wrong Function!\n");
    }

    return 0;
}
