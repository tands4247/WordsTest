import java.util.Random;
import java.io.*;

public class Test{
    private String english;     //英単語
    private String japanese;    //日本語訳
    private int no;             //四択のうち正解番号
    private String[] dummys = new String[100];  //ダミー
    static int count = 0;   //オブジェクトの作成数のカウント
    int ans;

    Random r = new Random();    //乱数のオブジェクト

    //コンストラクタ
    public Test(String en, String ja, String[] dum){
        english = en;
        japanese = ja;
        no = r.nextInt(4) + 1;  //1～4の乱数
        dummys = dum;
        count++;
    }

    public boolean decision(){
        return (ans == no);
    }

    public void test_start(int a) throws IOException{
        System.out.println(count+ "門. " +english);
        for(int j=1; j<=4; j++){
            if(j == no){
                System.out.print("（" +j+ "）" +japanese+ "   ");
            }
            else{
                System.out.print("（" +j+ "）" +dummys[r.nextInt(a)]+ "   ");
            }
        }
        System.out.print('\n');

        System.out.print("答えを半角数字で入力してください：");
        BufferedReader br = new BufferedReader( new InputStreamReader(System.in));
        String str1 = br.readLine();
        ans = Integer.parseInt(str1);

        if(decision()){
            System.out.println("正解です");
        }
        else{
            System.out.println("ブッブー");
            System.out.println(english+ "\t" +japanese);
        }
    }

}