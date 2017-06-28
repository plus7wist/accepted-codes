作者：申尚昆
链接：https://www.zhihu.com/question/49059234/answer/114437633
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

public class Main {
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		InputReader cin = new InputReader(System.in);
		PrintWriter cout = new PrintWriter(new OutputStreamWriter(System.out));
		

		
		cout.flush();
	}
	
	private static class InputReader {

	    public BufferedReader rea;
	    public StringTokenizer tok;

	    public InputReader(InputStream stream) {
	        rea = new BufferedReader(new InputStreamReader(stream), 32768);
	        tok = null;
	    }

	    public String next() {
	        while (tok == null || !tok.hasMoreTokens()) {
	            try {
	                tok = new StringTokenizer(rea.readLine());
	            } catch (IOException e) {
	                throw new RuntimeException(e);
	            }
	        }
	        return tok.nextToken();
	    }

	    public int nextInt() {
	        return Integer.parseInt(next());
	    }
	}
}