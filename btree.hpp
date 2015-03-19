#ifndef __MYUN2__BTREE__HPP__
#define __MYUN2__BTREE__HPP__

namespace myun2
{
	template <typename Alloc, typename Key, typename Value, unsigned int RecordSize=8>
	class btree
	{
	private:
		Alloc alc;
		struct node {
			Key k;
			Value v;
		};
		struct block {
			struct header {
				unsigned char used;
				unsigned char _reserved;	//	Locking Flag
				unsigned char _reserved2;
				unsigned char _reserved3;
				unsigned int left;
				unsigned int right;
				unsigned int _padding;

				header() {
					used = 0;
                    _reserved = 0;
                    _reserved2 = 0;
                    _reserved3 = 0;
                    left = 0;
                    right = 0;
                    _padding = 0;
				}
			} head;

			static const int NodeCount = RecordSize - (sizeof(header) / sizeof(node));
			node nodes[NodeCount];

			bool is_full() const { return head.used >= NodeCount; }
			void add(const node& n) {
				nodes[head.used] = n;
				head.used++;
			}
		};
		block root;
		void init() {
			if ( alc.empty() )
				root = allocate();
			else {
				root = *(block*)alc[0];
			}
		}
		block allocate() {
			block blk;
			alc.write(&blk);
			return blk;
		}
		block* _block(unsigned int i) { return (block*)alc[i]; }
		void put_block(unsigned int i, const block* blk) { return (block*)alc[i]; }

		void split(block& blk)
		{
			block new_block;

			for(unsigned int i=0; i<blk.head.used; i++)
			{
				blk.nodes[i]
			}
			alc.write(&new_block);
		}
	public:
		btree(){ init(); }
		btree(const Alloc& _alc) : alc(_alc) { init(); }

		void insert(const Key& key, const Value& value)
		{
			node n = { key, value };
			root.add(n);
			if ( root.is_full() ) { split(root); }
			alc.write(0, &root);
		}
	};
}

#endif//__MYUN2__BTREE__HPP__
