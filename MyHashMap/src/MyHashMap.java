public class MyHashMap<K, V> implements IMap<K, V> {
    private Entry<K, V> data[] = null;
    private int size;
    private static int DEFAULT_SIZE = 16;
    private static double DEFAULT_LOAD_FACTOR = 0.75;

    @Override
    public void put(K key, V val) {
        if (data == null) {
            data = new Entry[this.DEFAULT_SIZE];
        }

        if (this.size >= DEFAULT_SIZE * DEFAULT_LOAD_FACTOR) {
            reSize();
        }

        int index = getIndex(key, this.DEFAULT_SIZE);
        IMap.Entry<K, V> head = data[index];
        while (head != null) {
            if (head.getKey().equals(key)) {
                head.setValue(val);
                return;
            } else {
                head = head.getNext();
            }
        }
        data[index] = new Entry<>(key, val, data[index]);
        this.size++;
    }

    private void reSize() {
        System.out.println("Expanding...");
        Entry<K, V> newData[] = new Entry[DEFAULT_SIZE << 1];
        IMap.Entry<K, V> head = null;
        for (int i = 0; i < data.length; i++) {
            head = data[i];
            while (head != null) {
                int index = getIndex(head.getKey(), newData.length);
                IMap.Entry<K, V> next = head.getNext();
                head.setNext(newData[index]);
                newData[index] = (Entry<K, V>) head;
                head = next;
            }
        }
        this.data = newData;
        this.DEFAULT_SIZE = newData.length;
        newData = null;
    }

    @Override
    public V get(K key) {
        if (data == null)
            return null;

        int index = getIndex(key, this.DEFAULT_SIZE);
        IMap.Entry<K, V> head = data[index];
        while (head != null && !head.getKey().equals(key)) {
            head = head.getNext();
        }
        return head.getValue();
    }

    @Override
    public int size() {
        return this.size;
    }

    private int getIndex(K key, int defaultSize) {
        if (key == null) {
            return 0;
        }

        int hash = key.hashCode();
        return hash & (defaultSize - 1);
    }

    static class Entry<K, V> implements IMap.Entry<K, V> {
        K key;
        V value;
        IMap.Entry<K, V> next;

        public Entry(K key, V value, IMap.Entry<K, V> next) {
            this.key = key;
            this.value = value;
            this.next = next;
        }

        @Override
        public K getKey() {
            return this.key;
        }

        @Override
        public V getValue() {
            return this.value;
        }

        @Override
        public void setValue(V value) {
            this.value = value;
        }

        @Override
        public IMap.Entry<K, V> getNext() {
            return this.next;
        }

        @Override
        public void setNext(IMap.Entry<K, V> next) {
            this.next = next;
        }
    }
}
