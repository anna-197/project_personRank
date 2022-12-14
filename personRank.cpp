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

vector<int> getLikes(vector<string> tweets){
    vector<int> likes;
    for(int i = 0; i<tweets.size(); i++){
        string tweet = tweets[i];
        string likes_ans = " ";
        for(int j = tweet.length()-1; j >= 0; j--){
            if(tweet[j] != '\t')
                likes_ans = likes_ans+tweet[j];
            else
                break;
        }
        reverse(likes_ans.begin(), likes_ans.end());
        int intlikes = stoi(likes_ans);
        likes.push_back(intlikes);
    }
    return likes;
}

vector<string> getMentions(vector<string> tweets){
    vector<string> mentions;
    for(int i = 0; i<tweets.size(); i++){
        string tweet = tweets[i];
        string mention_ans = " ";
        // flag to check iterating of content only
        int flag = 0;
        for(int j = 0; j<tweet.length();j++){
            // skips user
            if(tweet[j] != '\t' && flag == 0){
                continue;
            }
            //increment till content starts
            if(flag == 0){
                j++;
            }
            // start of content
            flag = 1;
            if(tweet[j] != '@'){
                if(tweet[j] == '\t' && flag == 1){
                    break;
                }
                    continue;
            }
            // otherwise
            int k = j;
            while(tweet[k] != '\t' && tweet[k] != ' '){
                mention_ans = mention_ans+tweet[k];
                k++;
            }
            mentions.push_back(mention_ans);
            mention_ans = "";
                
            if(tweet[k] == '\t'){
                flag = 0;
                break;
            }
            j = k;
        }
    }
    return mentions;
}

vector<string> getUsername(vector<string> tweets){
    vector<string> users;
    for(int i = 0; i<tweets.size(); i++){
        string tweet = tweets[i];
        string ans = " ";
        for(int j = 0; j<tweet.length();j++){
            if(tweet[j] != '\t')
                ans = ans+tweet[j];
            else
                break;
        }
        users.push_back(ans);
    }
    return users;
}
    
bool sortVector(const pair<string,int> &a, const pair<string,int> &b){
    return (a.second < b.second);
}
    
void Solution(vector<string> tweets) {
    map<string,int> personRankMap;
    vector<string> users = getUsername(tweets);
    vector<int> num_of_likes = getLikes(tweets);
    // mapping users to likes
    for(int i = 0; i<users.size(); i++){
        if(personRankMap.find(users[i]) == personRankMap.end()){
            personRankMap.insert(make_pair(users[i],(num_of_likes[i]*10)));
        }
        else{
            personRankMap[users[i]] = personRankMap[users[i]]+(num_of_likes[i]*10);
        }
    }
    vector<string> mentions = getMentions(tweets);
    // mapping mentions to likes
    for(int i = 0; i<mentions.size(); i++){
        if(personRankMap.find(mentions[i]) == personRankMap.end()){
            personRankMap.insert(make_pair(mentions[i],50+(num_of_likes[i]*5)));
        }
        else{
            personRankMap[mentions[i]] = personRankMap[mentions[i]]+((num_of_likes[i]*5)+50);
        }
    }
    vector<pair<string, int> > personRankMapVector;
    // Copy key-value pair from Map
    // to vector of pairs
    for (auto& it : personRankMap) {
        personRankMapVector.push_back(it);
    }
    // sort vector
    sort(personRankMapVector.begin(), personRankMapVector.end(), sortVector);
    vector<pair<string, int>>::iterator ptr;
    //reverse printing vector
    //actual personRank
    cout<<"personRankMapVectorctual personRank"<<endl;
    for (ptr = personRankMapVector.end()-1; ptr >= personRankMapVector.begin(); ptr--)
        cout << ptr->first <<endl;
}
    

int main() {
    vector<string> tweets;
    read(tweets);
    Solution(tweets);
    return 0;
}        