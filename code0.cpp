#include <bits/stdc++.h>
using namespace std;
string substr(string x,int l,int r=-1){
	if(r==-1) r=x.length()-1;
	string res="";
	for(int i=l;i<=r;i++) res+=x[i];
	return res;
}
struct Problem{
	struct Link{
		string name;
		vector<pair<string,string> >p;
		Link(string _name=""){name=_name,p.clear();}
		void insert(string x,string y=""){
			if(y==""){
				string str="";
				for(int i=0;x[i]&&(x[i]<'0'||x[i]>'9');i++) str+=x[i];
				if(str=="P"){
					y="https://www.luogu.com.cn/problem/"+x;
				}
				if(str=="CF"){
					string tmp=substr(x,2),s1="",s2="";
					for(int i=0,flag=0;tmp[i];i++){
						if(!('0'<=tmp[i]&&tmp[i]<='9')) flag=1;
						if(flag) s2+=tmp[i];
						else s1+=tmp[i];
					}
					y="https://codeforces.com/problemset/problem/"+s1+"/"+s2;
				}
				if(str=="QOJ"){
					y="https://qoj.ac/problem/"+substr(x,3);
				}
			}
			if(y=="null") y="";
			p.push_back(make_pair(x,y));
		}
	};
	struct Sub{
		array<int,6>tim;
		string name,link;
		Sub(){for(int i=0;i<6;i++)tim[i]=0;name=link="";}
	};
	vector<Link>link;
	string difficulty;
	vector<pair<string,string>> from;
	vector<string>tag;
	vector<Sub>sub;
	Problem(){
		link.clear(),tag.clear();
		difficulty="";
		from.clear();
	}
	void update_link(vector<string>p){
		string name="";
		for(auto x:p){
			if(x[0]=='#') name=substr(x,1),link.push_back(Link(name));
			else if(name=="") continue;
			else{
				string s1="",s2="";
				for(int i=0,flag=0;x[i];i++){
					if(x[i]==';'&&!flag){flag=1;continue;}
					if(flag) s2+=x[i];
					else s1+=x[i];
				}
				link.back().insert(s1,s2);
			}
		}
	}
	void update_difficulty(vector<string>p){
		if(p.size()) difficulty=p[0];
	}
	void update_from(vector<string>p){
		for(auto x:p){
			string name="",link="";
			for(int i=0,flag=0;x[i];i++){
				if(x[i]==';'&&!flag){flag=1;continue;}
				if(!flag) name+=x[i];
				else link+=x[i];
			}
			from.push_back(make_pair(name,link));
		}
	}
	void update_tag(vector<string>p){
		for(auto x:p) tag.emplace_back(x);
	}
	void update_sub(vector<string>p){
		for(auto x:p){
			Sub tmp;
			for(int i=0,cnt=0,cnt1=0;x[i];i++){
				if(x[i]==';'){cnt++;continue;}
				if(cnt==0){
					if(x[i]=='-'||x[i]==':'||x[i]==' '){cnt1++;continue;}
					if(cnt1<=5&&'0'<=x[i]&&x[i]<='9') tmp.tim[cnt1]=tmp.tim[cnt1]*10+x[i]-'0'; 
				}
				if(cnt==1) tmp.name+=x[i];
				if(cnt==2) tmp.link+=x[i];
			}
			sub.push_back(tmp);
		}
		sort(sub.begin(),sub.end(),[&](Sub u,Sub v){return u.tim>v.tim;});
	}
	void work(string op,vector<string>p){
		if(op=="link"){update_link(p);return;}
		if(op=="df"){update_difficulty(p);return;}
		if(op=="from"){update_from(p);return;}
		if(op=="tag"){update_tag(p);return;}
		if(op=="sub"){update_sub(p);return;}
	}
	void print(){
		cout<<"## Basic\n\n";
		if(difficulty!="") cout<<"- **difficulty:** "<<difficulty<<"\n";
		if(from.size()){
			cout<<"- **from:**\n";
			for(auto x:from){
				cout<<"\t- ";
				if(x.second=="") cout<<x.first<<"\n";
				else cout<<"["<<x.first<<"]("<<x.second<<")\n";
			}
		}
		if(tag.size()){
			cout<<"- **tag:**\n";
			for(auto x:tag) cout<<"\t- "<<x<<"\n";
		}
		cout<<"\n";
		if(link.size()){
			cout<<"## Link\n\n";
			for(auto x:link){
				cout<<"- **"<<x.name<<"**\n";
				for(auto y:x.p){
					cout<<"\t- ";
					if(y.second=="") cout<<y.first<<"\n";
					else cout<<"["<<y.first<<"]("<<y.second<<")\n";
				}
			}
			cout<<"\n";
		}
		if(sub.size()){
			cout<<"## Submission\n\n";
			for(auto x:sub){
				printf("- **%d-%02d-%02d %02d:%02d:** ",x.tim[0],x.tim[1],x.tim[2],x.tim[3],x.tim[4]);
				cout<<x.name;
				if(x.link!="") cout<<" [submission]("<<x.link<<")";
				cout<<"\n";
			}
			cout<<"\n";
		}
	}
}problem;
vector<string>p;
int main(){
	freopen("P15142/problem.conf","r",stdin);
	freopen("P15142/index.md","w",stdout);
	string str;
	while(getline(cin,str)){
		int l=0,r=(int)str.length()-1;
		while(l<=r){
			if(str[l]==' '||str[l]=='\t') l++;
			else if(str[r]==' '||str[r]=='\t') r--;
			else break;
		}
		if(l>r) continue;
		p.emplace_back(substr(str,l,r));
	}
	int m=p.size();
	for(int i=0;i<m;i++){
		if(p[i][0]=='>'){
			int cnt=1,j=i+1;
			while(j<m){
				if(p[j][0]=='>') cnt++;
				if(p[j][0]=='<') cnt--;
				if(!cnt) break;
				j++;
			}
			if(j==m||substr(p[i],1)!=substr(p[j],1)) cerr<<"not match!";
			vector<string>q;
			for(int k=i+1;k<j;k++) q.push_back(p[k]);
			problem.work(substr(p[i],1),q);
			i=j;
		}
	}
	problem.print();
	return 0;
}