#include <iostream>
#include <vector>
#include <memory.h>
#include <ctime>
#define NUMG 10
using namespace std;

const int POPSIZE = 30;
const int CAPACITY = 40;
const int GENENUM = 8;
int Weight[NUMG]={6,9,8,8,6, 1, 10,5};
int Value[NUMG]={2,20,5,4,19,14,18,8};
int f[CAPACITY + 1];
const float pc = 0.9;
const float pm = 0.1;
vector<char> pop;
float fitness[POPSIZE];
void dp()
{
    for(int i = 0;i < NUMG;i++)
    {
        for(int j = CAPACITY;j >= Weight[i];j--)
        {
            f[j] = max(f[j],f[j - Weight[i]] + Value[i]);
        }
    }
    cout << f[CAPACITY] << endl;
}

void Init_Pop()
{
    for(int i = 0;i < POPSIZE;i++)
    {
        pop.push_back(rand() % 128);
    }
}

void Compute_Fitness()
{
    memset(fitness,0,sizeof(fitness));
    int all_sum = 0;
    for(int i = 0;i < POPSIZE;i++)
    {
        int sum_value = 0, sum_weight = 0;
        for(int j = 0;j < GENENUM;j++)
        {
            if((pop[i] >> j) & 1)
            {
                sum_value += Value[GENENUM - j - 1];
                sum_weight += Weight[GENENUM - j - 1];
            }
        }
        if(sum_weight > CAPACITY)
        {
            fitness[i] = 0;
        }
        else
        {
            fitness[i] = sum_value;
            all_sum += sum_value;
        }
    }
    for(int i = 0;i < POPSIZE;i++)
    {
        fitness[i] /= all_sum;
    }
}

int RWS()
{
    float m = 0,r = (float)(rand() % 10000) / 10000;
    for(int i = 0;i < POPSIZE;i++)
    {
        m += fitness[i];
        if(r <= m) return i;
    }
}

void ComputeV()
{
    for(int i = 0;i < POPSIZE;i++)
    {
        int sum_value = 0, sum_weight = 0;
        for(int j = 0;j < GENENUM;j++)
        {
            if((pop[i] >> j) & 1)
            {
                sum_value += Value[GENENUM - j - 1];
                sum_weight += Weight[GENENUM - j - 1];
            }
        }
        cout << sum_value << " " << sum_weight << endl;
    }
}

int main()
{
    srand(time(NULL));
    Init_Pop();
    for(int i = 0;i < 5000;i++)
    {
        Compute_Fitness();
        vector<char> temp;
        for(int j = 0;j < CAPACITY / 2;j++)
        {
            int p1 = RWS(),p2 = RWS();
            int pos = rand() % 8;
            char g1 = (pop[p1] & (255 << pos)) | ((255 >> (GENENUM - pos)) & pop[p2]);
            char g2 = (pop[p2] & (255 << pos)) | ((255 >> (GENENUM - pos)) & pop[p1]);
            if((float)(rand() % 1000) / 1000 < pm)
            {
                int ps1 = rand() % 8;
                if((g1 >> ps1) & 1) g1 = (g1 & (~(1 << ps1)));
                else g1 = (g1 | (1 << ps1));
                int ps2 = rand() % 8;
                if((g2 >> ps2) & 1) g2 = (g2 & (~(1 << ps2)));
                else g2 = (g2 | (1 << ps2));
            }
            temp.push_back(g1);
            temp.push_back(g2);
        }
        pop = temp;
    }
    ComputeV();
    dp();
    return 0;
}
