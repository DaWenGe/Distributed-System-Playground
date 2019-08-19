public class Test {
    public static void main(String[] args) {
        IMap<String, String> map = new MyHashMap<>();

        for (int i = 0; i < 32; i++) {
            map.put("No." + i, "Panghu" + i);
        }

        System.out.println(map.get("No.7"));
    }
}
