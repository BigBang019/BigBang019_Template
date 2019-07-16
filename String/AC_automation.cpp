namespace AC{
    typedef long long ll;
    using namespace std;
    const int N = 1e6 + 5;
    int nxt[N][30], fail[N], cnt[N];
    int tot, root;
    int newNODE(){
        tot++;
        for (int i = 0; i < 26;i++)
            nxt[tot][i] = -1;
        cnt[tot] = 0;
        return tot;
    }
    void init(){
        tot = 0;
        root = newNODE();
    }
    void update(char *s){
        int len = strlen(s);
        int now = root;
        for (int i = 0; i < len;i++)
        {
            int p = s[i] - 'a';
            if (nxt[now][p]==-1)
                nxt[now][p] = newNODE();
            now = nxt[now][p];
        }
        cnt[now]++;
    }
    void build(){
        queue<int> q;
        fail[root] = root;
        for (int i = 0; i < 26;i++)
        {
            if (nxt[root][i]==-1)
                nxt[root][i] = root;
            else{
                int x = nxt[root][i];
                fail[x] = root;
                q.push(x);
            }
        }
        while (!q.empty()){
            int now = q.front();                        //入队节点的失配指针已经建好
            q.pop();                                    //出队节点的nxt一定指向合法位
            for (int i = 0; i < 26;i++)
            {
                if (nxt[now][i]==-1)
                    nxt[now][i] = nxt[fail[now]][i];    //没有后继点则指向失配节点的下一个相应位置
                else{
                    int x = nxt[now][i];
                    fail[x] = nxt[fail[now]][i];        //失配指针指向父亲失配节点的相应位置
                    q.push(x);
                }
            }
        }
    }
    int query(char *s){
        int len = strlen(s);
        int now = root;
        int res = 0;
        for (int i = 0; i < len;i++)
        {
            int p = s[i] - 'a';
            now = nxt[now][p];
            int tmp = now;
            while (tmp!=root){
                res += cnt[tmp];
                cnt[tmp] = 0;           //已经被统计过，所以置0
                tmp = fail[tmp];        //利用失配来遍历当前字符所有位置
            }
        }
        return res;
    }
}
using namespace AC;