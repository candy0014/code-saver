#include <bits/stdc++.h>
#include <filesystem>
using namespace std;
ifstream in;
ofstream out;
string substr(string x,int l,int r=-1){
	if(r==-1) r=x.length()-1;
	string res="";
	for(int i=l;i<=r;i++) res+=x[i];
	return res;
}
string to_string0(int x,int d){
	string s="";
	for(int i=1;i<=d;i++) s=char(x%10+'0')+s,x/=10;
	return s;
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
				if(str=="LOJ"){
					y="https://loj.ac/p/"+substr(x,3);
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
	string name;
	vector<Link>link;
	int difficulty;
	vector<pair<string,string>> from;
	vector<string>tag;
	vector<Sub>sub;
	Problem(){
		link.clear(),tag.clear();
		difficulty=0;
		from.clear();
		name="";
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
		if(p.size()){
			for(auto x:p[0]) if('0'<=x&&x<='9') difficulty=difficulty*10+x-'0';
		}
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
		out<<"## Basic\n\n";
		if(difficulty) out<<"- **difficulty:** "<<difficulty<<"\n";
		if(from.size()){
			out<<"- **from:**\n";
			for(auto x:from){
				out<<"\t- ";
				if(x.second=="") out<<x.first<<"\n";
				else out<<"["<<x.first<<"]("<<x.second<<")\n";
			}
		}
		if(tag.size()){
			out<<"- **tag:**\n";
			for(auto x:tag) out<<"\t- "<<x<<"\n";
		}
		out<<"\n";
		if(link.size()){
			out<<"## Link\n\n";
			for(auto x:link){
				out<<"- **"<<x.name<<"**\n";
				for(auto y:x.p){
					out<<"\t- ";
					if(y.second=="") out<<y.first<<"\n";
					else out<<"["<<y.first<<"]("<<y.second<<")\n";
				}
			}
			out<<"\n";
		}
		if(sub.size()){
			out<<"## Submission\n\n";
			for(auto x:sub){
				out<<"- **"<<to_string0(x.tim[0],4)<<"-"<<to_string0(x.tim[1],2)<<"-"<<to_string0(x.tim[2],2)<<" "<<to_string0(x.tim[3],2)<<":"<<to_string0(x.tim[4],2)<<"** "<<x.name;
				if(x.link!="") out<<" [submission]("<<x.link<<")";
				out<<"\n";
			}
			out<<"\n";
		}
	}
	void print2(){
		out<<"{\n";
		out<<"\"name\": "<<"\""<<name<<"\""<<",\n";
		out<<"\"problems\": [";
		int flag=0;
		for(auto x:link){
			if(x.name=="Link"){
				for(auto y:x.p){
					if(flag) out<<",";
					flag=1;
					out<<"\""<<y.first<<"\"";
				}
			}
		}
		out<<"],\n";
		out<<"\"search\": [";
		flag=0;
		for(auto x:link){
			if(x.name=="Code"||x.name=="Solution") continue;
			for(auto y:x.p){
				if(flag) out<<",";
				flag=1;
				out<<"\""<<y.first<<"\"";
			}
		}
		out<<"],\n";
		out<<"\"difficulty\": "<<difficulty<<",\n";
		array<int,6>x;
		if(sub.size()) x=sub[0].tim;
		else x={0,0,0,0,0,0};
		out<<"\"time\": "<<"\""<<to_string0(x[0],4)<<"-"<<to_string0(x[1],2)<<"-"<<to_string0(x[2],2)<<" "<<to_string0(x[3],2)<<":"<<to_string0(x[4],2)<<":"<<to_string0(x[5],2)<<"\",\n";
		out<<"\"tags\": [";
		flag=0;
		for(auto x:tag){
			if(flag) out<<",";
			flag=1;
			out<<"\""<<x<<"\"";
		}
		out<<"]\n";
		out<<"}";
	}
};
vector<Problem>P;
int main(){
	for(const auto& file:filesystem::directory_iterator("./problems")) if(file.is_directory()){
		Problem problem;
		string s="";
		s=file.path();
		for(int i=s.length()-1;i>=0&&s[i]!='/';i--) problem.name=s[i]+problem.name;
		cerr<<problem.name<<"\n";
		s+="/raw";
		in.open(s+"/problem.conf",ios::in);
		if(!in.is_open()) continue;
		out.open(s+"/index.md",ios::out|ios::trunc);
		string str;
		vector<string>p;
		while(getline(in,str)){
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
		in.close(),out.close();
		P.push_back(problem);
	}
	out.open("./problems/index.json",ios::out|ios::trunc);
	out<<"[\n";
	for(int i=0;i<(int)P.size();i++){
		P[i].print2();
		if(i!=(int)P.size()-1) out<<",\n";
		else out<<"\n";
	}
	out<<"]";
	out.close();
	return 0;
}