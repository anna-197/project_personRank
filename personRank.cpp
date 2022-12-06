#include<bits/stdc++.h>
using namespace std;

void read(vector<string> &tweets) {
    ifstream newfile;
    newfile.open("tweets.txt",ios::in); 
    if (newfile.is_open()){
        string tweet; 
        while(getline(newfile, tweet)){
            tweets.push_back(tweet); 
        } 
        newfile.close(); 
    } 
}

vector<int> Likes(vector<string> tweets){
    vector<int> likes;
    for(int i=0; i<tweets.size(); i++){
        string word=tweets[i];
        string likes_ans=" ";
        for(int j=word.length()-1; j>=0; j--){
            if(word[j]!='\t')
                likes_ans=likes_ans+word[j];
            else
                break;
        }
        reverse(likes_ans.begin(), likes_ans.end());
        int intlikes = stoi(likes_ans);
        likes.push_back(intlikes);
    }
    return likes;
}

vector<string> Mention(vector<string> tweets){
    vector<string> mention;
    for(int i=0; i<tweets.size(); i++){
        string word=tweets[i];
        string mention_ans=" ";
        // flag to check iterating of content only
        int flag=0;
        for(int j=0; j<word.length();j++){
            // skips user
            if(word[j]!='\t' && flag==0){
                continue;
            }
            //increment till content starts
            if(flag==0){
                j++;
            }
            // start of content
            flag=1;
            if(word[j]!='@'){
                if(word[j]=='\t' && flag==1){
                    break;
                }
                    continue;
            }
            // otherwise
            int k=j;
            while(word[k]!='\t' && word[k]!=' '){
                mention_ans=mention_ans+word[k];
                k++;
            }
            mention.push_back(mention_ans);
            mention_ans="";
                
            if(word[k]=='\t'){
                flag=0;
                break;
            }
            j=k;
        }
    }
    return mention;
}

vector<string> User(vector<string> tweets){
    vector<string> user;
    for(int i=0; i<tweets.size(); i++){
        string word=tweets[i];
        string ans=" ";
        for(int j=0; j<word.length();j++){
            if(word[j]!='\t')
                ans=ans+word[j];
            else
                break;
        }
        user.push_back(ans);
    }
    return user;
}
    
bool sortbysec(const pair<string,int> &a, const pair<string,int> &b){
    return (a.second < b.second);
}
    
void Solution(vector<string> tweets) {
    map<string,int> mp;
    vector<string> user=User(tweets);
    vector<int> like=Likes(tweets);
    // mapping users to likes
    for(int i=0; i<user.size(); i++){
        if(mp.find(user[i])==mp.end()){
            mp.insert(make_pair(user[i],(like[i]*10)));
        }
        else{
            mp[user[i]]=mp[user[i]]+(like[i]*10);
        }
    }
    vector<string> mention=Mention(tweets);
    // mapping mentions to likes
    for(int i=0; i<mention.size(); i++){
        if(mp.find(mention[i])==mp.end()){
            mp.insert(make_pair(mention[i],50+(like[i]*5)));
        }
        else{
            mp[mention[i]]=mp[mention[i]]+((like[i]*5)+50);
        }
    }
    vector<pair<string, int> > A;
    // Copy key-value pair from Map
    // to vector of pairs
    for (auto& it : mp) {
        A.push_back(it);
    }
    // sort vector
    sort(A.begin(), A.end(), sortbysec);
    vector<pair<string, int>>::iterator ptr;
    //reverse printing vector
    //actual personRank
    cout<<"Actual personRank"<<endl;
    for (ptr = A.end()-1; ptr >= A.begin(); ptr--)
        cout << ptr->first <<endl;
}
    

int main() {
    vector<string> tweets;
    read(tweets);
    Solution(tweets);
    return 0;
}        