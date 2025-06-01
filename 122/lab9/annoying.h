template <typename TYPE>
void LinkedList<TYPE>::sort(int(*cmp)(const TYPE& item1, const TYPE& item2), bool doQuicksort)
{
    Node<TYPE>* t2 = nullptr;

    bool swapped = true;
    while(swapped)
    {
        swapped = false;
        
        t2 = head;
        
        for (int i = 0; i < count - 2; i++)
        {
            if(cmp(t2->data, t2->next->data) > 0)
            {
                 Node<TYPE>* t3 = t2->next;
                 Node<TYPE>* t4 = t2->next->next;
                 Node<TYPE>* t1 = t2->prev;
                 
                 if(t2 == head) // head
                 {
                     t4->prev = t2;
                     t3->next = t2;
                     t2->prev = t3;
                     t2->next = t4;
                     head = t3;
                 }
                 else if(t2 == tail->prev) // penultimate (t2 will never equal tail. so this is the last iteration.)
                 {
                     t1->next = t3;
                     t3->prev = t1;
                     t3->next = t2;
                     t2->prev = t3;
                     tail = t2;
                 }
                 else
                 {
                     t4->prev = t2;
                     t1->next = t3;
                     t3->prev = t1;
                     t3->next = t2;
                     t2->prev = t3;
                     t2->next = t4;
                 }
                swapped = true;
            }
            
            //This is a method that only swaps data not pointers.
            /*{
                TYPE temp = t2 -> data;
                t2->data = t2 -> next ->data;
                t2 -> next -> data = temp;
                
                swapped = true;
            }*/
            t2 = t2->next;
        }
    }
}
