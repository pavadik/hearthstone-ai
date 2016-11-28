﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;

namespace HearthstoneAI.Board
{
    [DataContract]
    class Hand
    {
        [DataMember]
        public List<string> cards = new List<string>();

        public bool Parse(GameState game, GameState.Entity player)
        {
            bool ret = true;

            int controller = player.GetTagOrDefault(GameTag.CONTROLLER, -1);
            if (controller < 0) return false;

            SortedDictionary<int, string> sorted_cards = new SortedDictionary<int, string>();

            foreach (var entity in game.Entities)
            {
                if (entity.Value.GetTagOrDefault(GameTag.CONTROLLER, controller - 1) != controller) continue;

                if (!entity.Value.HasTag(GameTag.ZONE)) continue;
                if (entity.Value.GetTag(GameTag.ZONE) != (int)TAG_ZONE.HAND) continue;

                var zone_pos = entity.Value.GetTagOrDefault(GameTag.ZONE_POSITION, -1);
                if (zone_pos < 0) ret = false;

                sorted_cards.Add(zone_pos, entity.Value.CardId);
            }

            foreach (var sorted_card in sorted_cards)
            {
                this.cards.Add(sorted_card.Value);
            }

            return ret;
        }

        public override bool Equals(object obj)
        {
            Hand rhs = obj as Hand;
            if (rhs == null) return false;
            return this.cards.SequenceEqual(rhs.cards);
        }

        public override int GetHashCode()
        {
            int hash = HashHelper.init;
            foreach (var card in this.cards)
                HashHelper.Update(ref hash, card);
            return hash;
        }
    }
}