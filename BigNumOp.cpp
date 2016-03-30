//by vito
#include <iostream>
#include <string>
#include <cstring>

using namespace std;


class big{
public:
    int length;
    string origin;

    //construct function
    big(){
        origin.clear();
        
    }
    //construct function with param: string
    big(string a){
        if(!origin.empty()) origin.clear();
        length=(int)a.size();
        origin=a;
    }
    
    string operator+(const big& comp){
        string temp;
        temp=comp.origin;
        int carry=0;
        int maxlen;
        //add 0
        //left one is bigger than right's
        if(length>comp.length){
            maxlen=length;
            for(int i=0;i<length-comp.length;i++){
                temp.insert(temp.begin(), '0');
            }
        }
        //right one is bigger than left's
        else{
            maxlen=comp.length;
            for(int i=0;i<comp.length-length;i++){
                origin.insert(origin.begin(), '0');
            }
        }
        string sum(maxlen ,'0');
        for(int j=maxlen-1;j>=0;j--){
            carry=(int)(origin[j]-'0')+(int)(temp[j]-'0')+carry;
            sum[j]=(carry%10+'0');
            carry/=10;
        }
        if(carry!=0)
            sum.insert(sum.begin(),(carry%10+'0'));
        return sum;
    }
    
    string operator-(const big& comp)
    {
        
        string head;    //wether need add minus symbol
        string temp;
        temp=comp.origin;
        int borrow=0;
        int maxlen;
        
        //check if numbers are same
        if(origin==temp)
            return "0";
        
        //add 0
        //left one is bigger than right's
        if(length>comp.length){
            maxlen=length;
            for(int i=0;i<length-comp.length;i++){
                temp.insert(temp.begin(), '0');
            }
            
        }
        //right one is bigger than left's
        else{
            maxlen=comp.length;
            for(int i=0;i<comp.length-length;i++){
                origin.insert(origin.begin(), '0');
            }
        }
        
        // initialize the different 
        string result(maxlen ,'0');
        
        //if it is bigger one to minus smaller's
        for(int i=0;i<maxlen;i++){
            if(origin[i]>temp[i])
                break;
            else if(origin[i]==temp[i])
                continue;
            else{
                string ch;
                ch=origin;
                origin=temp;
                temp=ch;
                head="-";
                break;
            }
        }s        if(result[0]=='0')
            result.erase(result.begin());
        return (head+result);
    }
    
    string operator*(const big& comp){
        string temp;
        temp=comp.origin;
        int maxlen;
        int carry = 0;

        if(origin=="0"||temp=="0")
            return "0";
        
        maxlen=length+comp.length;
        string result(maxlen,'0');
        
        for(int j=comp.length-1;j>=0;j--){
            carry=0;        //reset carry one 
            for(int i=length-1;i>=0;i--){
                carry=(origin[i]-'0')*(temp[j]-'0')+carry+(result[i+j+1]-'0');  
                result[i+j+1]=(carry%10+'0');
                carry=carry/10;
            }          
            if(carry!=0){
                result[j]=carry+'0';
            }
        }
        //remove redundant 0
        if(carry==0)
            result=result.substr(1,maxlen-1);
        else{
            result[0]=carry+'0';
        }
        return result;
    

    
}
    
    string operator/(const big& comp){
        string temp=comp.origin,
        temp_origin=origin;
        
        int borrow= 0;
        
        //divisor is smaller than dividend
        if(temp_origin<=temp&&length<=comp.length){
            if(temp_origin==temp)
                return "1";
            else
                return "0";
        }
        
        int dif=length-comp.length;     
        string result(dif+1,'0');
        string minus(length,'0');
        
        
        for(int i=0;i<=dif;i++)     
        {
            //add 0 
            temp.append(dif-i,'0');
            temp.insert(temp.begin(),i,'0');
            
            
            for(int add=1;temp_origin>=temp;add++)  
            {
                //do minus 
                for (int j=length-1;j>=0;j--){
                    borrow=10+(int)(temp_origin[j]-'0')-(int)(temp[j]-'0')-borrow;
                    minus[j]=(borrow%10+'0');
                    borrow=1-borrow/10;
                }
                temp_origin=minus;
                result[i]='0'+add;
            }
            temp=comp.origin;   //reset dividend 
        }
        
        
        if(result[0]=='0')
            result.erase(result.begin());
        return result;
        
    }

};


int main(){
    string a,b;
    cin >> a;
    char o;
    cin >>o;
    cin >>b;
    big first(a);
    big second(b);
    string answer;
    if(o=='+')
        answer=first+second;
    if(o=='-')
        answer=first-second;
    if(o=='*')
        answer=first*second;
    if(o=='/')
        answer=first/second;
    cout << answer;
    return 0;

}
