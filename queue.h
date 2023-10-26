#define Q_SIZE (1)

typedef struct {
	unsigned char Data[Q_SIZE];
	unsigned int Head;
	unsigned int Tail;
	unsigned int Size;
} Q_T;

void Q_Init(Q_T *q) {
	unsigned int i;
	for (i=0; i<Q_SIZE; i++) {
		q->Data[i] = 0;
	}
	q->Head = 0;
	q->Tail = 0;
	q->Size = 0;
}

int Q_Empty(Q_T *q) {
	return q->Size == 0;
}

int Q_Full(Q_T *q) {
	return q->Size == Q_SIZE;
}

void Q_Enqueue(Q_T *q, unsigned char d) {
	if(!Q_Full(q)) {
		q->Data[q->Tail++] = d;
		q->Tail %= Q_SIZE;
		q->Size++;
	}
}

unsigned char Q_Dequeue(Q_T *q) {
	unsigned char t=0;
	if(!Q_Empty(q)) {
		t = q->Data[q->Head];
		q->Data[q->Head++] = 0;
		q->Head %= Q_SIZE;
		q->Size--;
	}
	return t;
}
