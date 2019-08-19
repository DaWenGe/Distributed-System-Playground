public interface IMap<K, V> {
    public void put(K key, V val);
    public V get(K key);
    public int size();

    interface Entry<K, V> {
        K getKey();
        V getValue();
        void setValue(V value);
        Entry<K, V> getNext();
        void setNext(Entry<K, V> next);
    }
}
